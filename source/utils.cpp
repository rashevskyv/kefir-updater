#include "utils.hpp"

#include <switch.h>

#include <chrono>
#include <filesystem>
#include <fstream>
#include <thread>

#include "current_cfw.hpp"
#include "download.hpp"
#include "extract.hpp"
#include "fs.hpp"
#include "main_frame.hpp"
#include "progress_event.hpp"
#include "reboot_payload.h"
#include "unistd.h"
#include "utils.hpp"

namespace i18n = brls::i18n;
using namespace i18n::literals;

// Макрос для умовного логування
#define DEBUG_LOG(logFile, message) \
    if (util::isDebugLoggingEnabled()) { \
        logFile << message; \
    }

namespace util {

    bool isDebugLoggingEnabled()
    {
        nlohmann::ordered_json config = fs::parseJsonFile(CONFIG_FILE);
        if (config.contains("debug_logging")) {
            return config["debug_logging"].get<bool>();
        }
        return false; // По замовчуванню вимкнено
    }

    bool isArchive(const std::string& path)
    {
        if (std::filesystem::exists(path)) {
            std::ifstream is(path, std::ifstream::binary);
            char zip_signature[4] = {0x50, 0x4B, 0x03, 0x04};  // zip signature header PK\3\4
            char signature[4];
            is.read(signature, 4);
            if (is.good() && std::equal(std::begin(signature), std::end(signature), std::begin(zip_signature), std::end(zip_signature))) {
                return true;
            }
        }
        return false;
    }

    void downloadArchive(const std::string& url, contentType type)
    {
        long status_code;
        downloadArchive(url, type, status_code);
    }

    void downloadArchive(const std::string& url, contentType type, long& status_code)
    {
        bool logging = util::isDebugLoggingEnabled();
        std::ofstream logFile;

        if (logging) {
            logFile.open(DEBUG_LOG_FILE, std::ios::app);
            logFile << "======================================" << std::endl;
            logFile << "=== downloadArchive START ===" << std::endl;
            logFile << "Timestamp: " << time(nullptr) << std::endl;
            logFile << "URL: " << url << std::endl;
            logFile << "contentType: " << static_cast<int>(type) << std::endl;
            logFile << "Creating download path: " << DOWNLOAD_PATH << std::endl;
        }

        fs::createTree(DOWNLOAD_PATH);

        if (logging) logFile << "Calling cleanup()..." << std::endl;
        cleanup();
        if (logging) logFile << "cleanup() completed" << std::endl;

        switch (type) {
            case contentType::custom:
                if (logging) logFile << "Type: custom, downloading to: " << CUSTOM_FILENAME << std::endl;
                status_code = download::downloadFile(url, CUSTOM_FILENAME, OFF);
                break;
            case contentType::cheats:
                if (logging) logFile << "Type: cheats, downloading to: " << CHEATS_FILENAME << std::endl;
                status_code = download::downloadFile(url, CHEATS_FILENAME, OFF);
                break;
            case contentType::fw:
                if (logging) logFile << "Type: fw, downloading to: " << FIRMWARE_FILENAME << std::endl;
                status_code = download::downloadFile(url, FIRMWARE_FILENAME, OFF);
                break;
            case contentType::app:
                {
                    if (logging) {
                        logFile << "========================================" << std::endl;
                        logFile << "Type: app (DBI)" << std::endl;
                        logFile << "DOWNLOADING FROM: " << url << std::endl;
                        logFile << "DOWNLOADING TO: " << APP_FILENAME_TEMP << std::endl;
                        logFile << "FINAL LOCATION WILL BE: " << APP_FILENAME << std::endl;
                        logFile << "Before download - temp file exists: " << std::filesystem::exists(APP_FILENAME_TEMP) << std::endl;
                        logFile << "Before download - final file exists: " << std::filesystem::exists(APP_FILENAME) << std::endl;
                        logFile << "Starting download..." << std::endl;
                    }

                    status_code = download::downloadFile(url, APP_FILENAME_TEMP, OFF);

                    if (logging) {
                        logFile << "Download completed with status: " << status_code << std::endl;
                        logFile << "After download - temp file exists: " << std::filesystem::exists(APP_FILENAME_TEMP) << std::endl;

                        if (std::filesystem::exists(APP_FILENAME_TEMP)) {
                            auto size = std::filesystem::file_size(APP_FILENAME_TEMP);
                            logFile << "Temp file size: " << size << " bytes (" << (size / 1024.0 / 1024.0) << " MB)" << std::endl;
                        } else {
                            logFile << "ERROR: Temp file does not exist after download!" << std::endl;
                        }
                    }

                    // If download failed, remove incomplete temp file
                    if (status_code != 200) {
                        if (logging) logFile << "Download FAILED (status != 200), removing temp file..." << std::endl;
                        if (std::filesystem::exists(APP_FILENAME_TEMP)) {
                            std::filesystem::remove(APP_FILENAME_TEMP);
                            if (logging) logFile << "DELETED incomplete temp file: " << APP_FILENAME_TEMP << std::endl;
                        } else {
                            if (logging) logFile << "Temp file already doesn't exist" << std::endl;
                        }
                    } else {
                        // Download successful - rename temp to final immediately
                        if (logging) {
                            logFile << "Download SUCCESS (status == 200)" << std::endl;
                            logFile << "Starting immediate rename..." << std::endl;
                        }

                        if (std::filesystem::exists(APP_FILENAME_TEMP)) {
                            if (std::filesystem::exists(APP_FILENAME)) {
                                if (logging) logFile << "DELETING old file: " << APP_FILENAME << std::endl;
                                std::filesystem::remove(APP_FILENAME);
                            }

                            if (logging) {
                                logFile << "RENAMING:" << std::endl;
                                logFile << "  FROM: " << APP_FILENAME_TEMP << std::endl;
                                logFile << "  TO:   " << APP_FILENAME << std::endl;
                            }
                            std::filesystem::rename(APP_FILENAME_TEMP, APP_FILENAME);

                            if (logging) {
                                logFile << "Rename completed" << std::endl;
                                if (std::filesystem::exists(APP_FILENAME)) {
                                    auto finalSize = std::filesystem::file_size(APP_FILENAME);
                                    logFile << "Final file size: " << finalSize << " bytes (" << (finalSize / 1024.0 / 1024.0) << " MB)" << std::endl;
                                }
                            }

                            // Copy forwarder
                            if (logging) {
                                logFile << "Copying forwarder:" << std::endl;
                                logFile << "  FROM: " << ROMFS_FORWARDER << std::endl;
                                logFile << "  TO:   " << FORWARDER_PATH << std::endl;
                            }
                            fs::copyFile(ROMFS_FORWARDER, FORWARDER_PATH);
                            if (logging) logFile << "Forwarder copied successfully" << std::endl;
                        }

                        if (logging) {
                            logFile << "DBI installation complete" << std::endl;
                            logFile << "========================================" << std::endl;
                        }
                    }
                }
                break;
            case contentType::bootloaders:
                if (logging) logFile << "Type: bootloaders, downloading to: " << BOOTLOADER_FILENAME << std::endl;
                status_code = download::downloadFile(url, BOOTLOADER_FILENAME, OFF);
                break;
            case contentType::ams_cfw:
                if (logging) logFile << "Type: ams_cfw, downloading to: " << AMS_FILENAME << std::endl;
                status_code = download::downloadFile(url, AMS_FILENAME, OFF);
                break;
            default:
                if (logging) logFile << "Unknown type!" << std::endl;
                break;
        }

        if (logging) {
            logFile << "Final status_code: " << status_code << std::endl;
            logFile << "Setting ProgressEvent status_code..." << std::endl;
        }
        ProgressEvent::instance().setStatusCode(status_code);

        if (logging) {
            logFile << "=== downloadArchive END ===" << std::endl;
            logFile << "======================================" << std::endl << std::endl;
            logFile.close();
        }
    }

    void showDialogBoxInfo(const std::string& text)
    {
        brls::Dialog* dialog;
        dialog = new brls::Dialog(text);
        brls::GenericEvent::Callback callback = [dialog](brls::View* view) {
            dialog->close();
        };
        dialog->addButton("menus/common/ok"_i18n, callback);
        dialog->setCancelable(true);
        dialog->open();
    }

    int showDialogBoxBlocking(const std::string& text, const std::string& opt)
    {
        int result = -1;
        brls::Dialog* dialog = new brls::Dialog(text);
        brls::GenericEvent::Callback callback = [dialog, &result](brls::View* view) {
            result = 0;
            dialog->close();
        };
        dialog->addButton(opt, callback);
        dialog->setCancelable(false);
        dialog->open();
        while (result == -1) {
            std::this_thread::sleep_for(std::chrono::microseconds(10));
        }
        std::this_thread::sleep_for(std::chrono::microseconds(800000));
        return result;
    }

    int showDialogBoxBlocking(const std::string& text, const std::string& opt1, const std::string& opt2)
    {
        int result = -1;
        brls::Dialog* dialog = new brls::Dialog(text);
        brls::GenericEvent::Callback callback1 = [dialog, &result](brls::View* view) {
            result = 0;
            dialog->close();
        };
        brls::GenericEvent::Callback callback2 = [dialog, &result](brls::View* view) {
            result = 1;
            dialog->close();
        };
        dialog->addButton(opt1, callback1);
        dialog->addButton(opt2, callback2);
        dialog->setCancelable(false);
        dialog->open();
        while (result == -1) {
            std::this_thread::sleep_for(std::chrono::microseconds(10));
        }
        std::this_thread::sleep_for(std::chrono::microseconds(800000));
        return result;
    }

    void crashIfNotArchive(contentType type)
    {
        if (!util::isDebugLoggingEnabled()) {
            // Швидкий шлях без логування
            std::string filename;
            switch (type) {
                case contentType::custom:
                    filename = CUSTOM_FILENAME;
                    break;
                case contentType::cheats:
                    filename = CHEATS_FILENAME;
                    break;
                case contentType::fw:
                    filename = FIRMWARE_FILENAME;
                    break;
                case contentType::app:
                    return; // DBI is .nro, skip check
                case contentType::bootloaders:
                    filename = BOOTLOADER_FILENAME;
                    break;
                case contentType::ams_cfw:
                    filename = AMS_FILENAME;
                    break;
                default:
                    return;
            }
            if (!isArchive(filename)) {
                ProgressEvent::instance().setStatusCode(406);
                ProgressEvent::instance().setStep(ProgressEvent::instance().getMax());
            }
            return;
        }

        // З логуванням
        std::ofstream logFile(DEBUG_LOG_FILE, std::ios::app);
        logFile << "=== crashIfNotArchive called ===" << std::endl;
        logFile << "contentType: " << static_cast<int>(type) << std::endl;

        std::string filename;
        switch (type) {
            case contentType::custom:
                filename = CUSTOM_FILENAME;
                break;
            case contentType::cheats:
                filename = CHEATS_FILENAME;
                break;
            case contentType::fw:
                filename = FIRMWARE_FILENAME;
                break;
            case contentType::app:
                // DBI is a .nro file, not an archive - skip check
                logFile << "contentType::app - skipping archive check (DBI is .nro)" << std::endl;
                logFile << "=== crashIfNotArchive end ===" << std::endl << std::endl;
                logFile.close();
                return;
            case contentType::bootloaders:
                filename = BOOTLOADER_FILENAME;
                break;
            case contentType::ams_cfw:
                filename = AMS_FILENAME;
                break;
            default:
                logFile << "Unknown contentType, returning" << std::endl;
                logFile.close();
                return;
        }
        logFile << "Checking file: " << filename << std::endl;
        logFile << "File exists: " << std::filesystem::exists(filename) << std::endl;

        if (!isArchive(filename)) {
            logFile << "ERROR: File is not an archive! Setting error 406" << std::endl;
            ProgressEvent::instance().setStatusCode(406);
            ProgressEvent::instance().setStep(ProgressEvent::instance().getMax());
        } else {
            logFile << "File is a valid archive" << std::endl;
        }

        logFile << "=== crashIfNotArchive end ===" << std::endl << std::endl;
        logFile.close();
    }

    void extractArchive(contentType type, const std::string& version)
    {
        bool logging = util::isDebugLoggingEnabled();
        std::ofstream logFile;

        if (logging) {
            logFile.open(DEBUG_LOG_FILE, std::ios::app);
            logFile << "======================================" << std::endl;
            logFile << "=== extractArchive START ===" << std::endl;
            logFile << "Timestamp: " << time(nullptr) << std::endl;
            logFile << "contentType: " << static_cast<int>(type) << std::endl;
            logFile << "version: " << version << std::endl;
            logFile << "Changing dir to: " << ROOT_PATH << std::endl;
        }

        chdir(ROOT_PATH);

        if (logging) logFile << "Calling crashIfNotArchive()..." << std::endl;
        crashIfNotArchive(type);
        if (logging) logFile << "crashIfNotArchive() completed" << std::endl;

        switch (type) {
            case contentType::cheats: {
                std::vector<std::string> titles = extract::getInstalledTitlesNs();
                titles = extract::excludeTitles(CHEATS_EXCLUDE, titles);
                extract::extractCheats(CHEATS_FILENAME, titles, CurrentCfw::running_cfw, version);
                break;
            }
            case contentType::fw:
                fs::removeDir(FIRMWARE_PATH);
                fs::createTree(FIRMWARE_PATH);
                extract::extract(FIRMWARE_FILENAME, FIRMWARE_PATH);
                if (std::filesystem::exists(FIRMWARE_FILENAME)) std::filesystem::remove(FIRMWARE_FILENAME);
                break;
            case contentType::app:
                // DBI installation is now handled in downloadArchive() immediately after download
                if (logging) {
                    logFile << "contentType::app - installation already completed in downloadArchive()" << std::endl;
                }
                break;
            case contentType::custom: {
                int preserveInis = showDialogBoxBlocking("menus/utils/overwrite_inis"_i18n, "menus/common/yes"_i18n, "menus/common/no"_i18n);
                extract::extract(CUSTOM_FILENAME, ROOT_PATH, preserveInis);
                break;
            }
            case contentType::bootloaders: {
                int preserveInis = showDialogBoxBlocking("menus/utils/overwrite_inis"_i18n, "menus/common/yes"_i18n, "menus/common/no"_i18n);
                extract::extract(BOOTLOADER_FILENAME, ROOT_PATH, preserveInis);
                break;
            }
            case contentType::ams_cfw: {
                if (std::filesystem::exists(KEFIR_DIRECTORY_PATH)) std::filesystem::remove_all(KEFIR_DIRECTORY_PATH);
                std::filesystem::create_directory(KEFIR_DIRECTORY_PATH);
                extract::extract(CFW_FILENAME, KEFIR_DIRECTORY_PATH, 1);

                if (std::filesystem::exists("/kefir/bootloader/hekate_ipl.ini")) {
                    fs::copyFile("/kefir/bootloader/hekate_ipl.ini", "/bootloader/hekate_ipl.ini");
                    fs::copyFile("/kefir/config/kefir-updater/kefir_updater.ini", "/bootloader/ini/!kefir_updater.ini");
                    fs::copyFile("/kefir/bootloader/res/ku.bmp", "/bootloader/res/ku.bmp");
                    if (std::filesystem::exists(CFW_FILENAME)) std::filesystem::remove_all(CFW_FILENAME);
                }
                break;
            }
            default:
                break;
        }
        if (type == contentType::ams_cfw || type == contentType::bootloaders || type == contentType::custom)
            fs::copyFiles(COPY_FILES_TXT);

        if (logging) {
            logFile << "=== extractArchive END ===" << std::endl;
            logFile << "======================================" << std::endl << std::endl;
            logFile.close();
        }
    }

    std::string formatListItemTitle(const std::string& str, size_t maxScore)
    {
        size_t score = 0;
        for (size_t i = 0; i < str.length(); i++) {
            score += std::isupper(str[i]) ? 4 : 3;
            if (score > maxScore) {
                return str.substr(0, i - 1) + "\u2026";
            }
        }
        return str;
    }

    std::string formatApplicationId(u64 ApplicationId)
    {
        return fmt::format("{:016X}", ApplicationId);
    }

    std::vector<std::string> fetchPayloads()
    {
        std::vector<std::string> payloadPaths;
        payloadPaths.push_back(ROOT_PATH);
        if (std::filesystem::exists(PAYLOAD_PATH)) payloadPaths.push_back(PAYLOAD_PATH);
        if (std::filesystem::exists(AMS_PATH)) payloadPaths.push_back(AMS_PATH);
        if (std::filesystem::exists(BOOTLOADER_PATH)) payloadPaths.push_back(BOOTLOADER_PATH);
        if (std::filesystem::exists(BOOTLOADER_PL_PATH)) payloadPaths.push_back(BOOTLOADER_PL_PATH);
        if (std::filesystem::exists(ROMFS_PATH)) payloadPaths.push_back(ROMFS_PATH);
        std::vector<std::string> res;
        for (const auto& path : payloadPaths) {
            for (const auto& entry : std::filesystem::directory_iterator(path)) {
                if (entry.path().extension().string() == ".bin") {
                    if (entry.path().string() != FUSEE_SECONDARY && entry.path().string() != FUSEE_MTC)
                        res.push_back(entry.path().string().c_str());
                }
            }
        }
        return res;
    }

    void shutDown(bool reboot)
    {
        spsmInitialize();
        spsmShutdown(reboot);
    }

    void rebootToPayload(const std::string& path)
    {
        reboot_to_payload(path.c_str(), CurrentCfw::running_cfw != CFW::ams);
    }

    std::string getLatestTag(const std::string& url)
    {
        nlohmann::ordered_json tag;
        download::getRequest(url, tag, {"accept: application/vnd.github.v3+json"});

        if (util::isDebugLoggingEnabled()) {
            std::ofstream logFile(DEBUG_LOG_FILE, std::ios::app);
            logFile << "=== getLatestTag ===" << std::endl;
            logFile << "URL: " << url << std::endl;
            logFile << "Response contains tag_name: " << (tag.find("tag_name") != tag.end()) << std::endl;
            if (tag.find("tag_name") != tag.end()) {
                logFile << "tag_name value: " << tag["tag_name"] << std::endl;
            } else {
                logFile << "Full response: " << tag.dump(2) << std::endl;
            }
            logFile << "===================" << std::endl << std::endl;
            logFile.close();
        }

        if (tag.find("tag_name") != tag.end())
            return tag["tag_name"];
        else
            return "";
    }

    std::string downloadFileToString(const std::string& url)
    {
        std::vector<uint8_t> bytes;
        download::downloadFile(url, bytes);
        std::string str(bytes.begin(), bytes.end());
        return str;
    }

    std::string getCheatsVersion()
    {
        std::string res = util::downloadFileToString(CHEATS_URL_VERSION);
        /* if (res == "" && isArchive(CHEATS_FILENAME)) {
            res = "offline";
        } */
        return res;
    }

    void saveToFile(const std::string& text, const std::string& path)
    {
        std::ofstream file(path);
        file << text << std::endl;
    }

    std::string readFile(const std::string& path)
    {
        std::string text = "";
        std::ifstream file(path);
        if (file.good()) {
            file >> text;
        }
        return text;
    }

    std::string getAppPath()
    {
        if (envHasArgv()) {
            std::smatch match;
            std::string argv = (char*)envGetArgv();
            if (std::regex_match(argv, match, std::regex(NRO_PATH_REGEX))) {
                if (match.size() >= 2) {
                    return match[1].str();
                }
            }
        }
        return NRO_PATH;
    }

    void restartApp()
    {
        std::string path = "sdmc:" + getAppPath();
        std::string argv = "\"" + path + "\"";
        envSetNextLoad(path.c_str(), argv.c_str());
        romfsExit();
        brls::Application::quit();
    }

    bool isErista()
    {
        SetSysProductModel model;
        setsysGetProductModel(&model);
        return (model == SetSysProductModel_Nx || model == SetSysProductModel_Copper);
    }

    void removeSysmodulesFlags(const std::string& directory)
    {
        for (const auto& e : std::filesystem::recursive_directory_iterator(directory)) {
            if (e.path().string().find("boot2.flag") != std::string::npos) {
                std::filesystem::remove(e.path());
            }
        }
    }

    std::string lowerCase(const std::string& str)
    {
        std::string res = str;
        std::for_each(res.begin(), res.end(), [](char& c) {
            c = std::tolower(c);
        });
        return res;
    }

    std::string upperCase(const std::string& str)
    {
        std::string res = str;
        std::for_each(res.begin(), res.end(), [](char& c) {
            c = std::toupper(c);
        });
        return res;
    }

    std::string getErrorMessage(long status_code)
    {
        std::string res;
        switch (status_code) {
            case 500:
                res = fmt::format("{0:}: Internal Server Error", status_code);
                break;
            case 503:
                res = fmt::format("{0:}: Service Temporarily Unavailable", status_code);
                break;
            default:
                res = fmt::format("error: {0:}", status_code);
                break;
        }
        return res;
    }

    bool isApplet()
    {
        AppletType at = appletGetAppletType();
        return at != AppletType_Application && at != AppletType_SystemApplication;
    }

    std::set<std::string> getExistingCheatsTids()
    {
        std::string path = getContentsPath();
        std::set<std::string> res;
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            std::string cheatsPath = entry.path().string() + "/cheats";
            if (std::filesystem::exists(cheatsPath)) {
                res.insert(util::upperCase(cheatsPath.substr(cheatsPath.length() - 7 - 16, 16)));
            }
        }
        return res;
    }

    std::string getContentsPath()
    {
        std::string path;
        switch (CurrentCfw::running_cfw) {
            case CFW::ams:
                path = std::string(AMS_PATH) + std::string(CONTENTS_PATH);
                break;
        }
        return path;
    }

    bool getBoolValue(const nlohmann::ordered_json& jsonFile, const std::string& key)
    {
        return (jsonFile.find(key) != jsonFile.end()) ? jsonFile.at(key).get<bool>() : false;
    }

    const nlohmann::ordered_json getValueFromKey(const nlohmann::ordered_json& jsonFile, const std::string& key)
    {
        return (jsonFile.find(key) != jsonFile.end()) ? jsonFile.at(key) : nlohmann::ordered_json::object();
    }

    int openWebBrowser(const std::string url)
    {
        Result rc = 0;
        int at = appletGetAppletType();
        if (at == AppletType_Application) {  // Running as a title
            WebCommonConfig conf;
            WebCommonReply out;
            rc = webPageCreate(&conf, url.c_str());
            if (R_FAILED(rc))
                return rc;
            webConfigSetJsExtension(&conf, true);
            webConfigSetPageCache(&conf, true);
            webConfigSetBootLoadingIcon(&conf, true);
            webConfigSetWhitelist(&conf, ".*");
            rc = webConfigShow(&conf, &out);
            if (R_FAILED(rc))
                return rc;
        }
        else {  // Running under applet
            showDialogBoxInfo("menus/utils/applet_webbrowser"_i18n);
        }
        return rc;
    }

}  // namespace util

void cleanup()
{
    if (!util::isDebugLoggingEnabled()) {
        // Швидкий шлях без логування
        std::filesystem::remove(AMS_FILENAME);
        std::filesystem::remove(APP_FILENAME_TEMP);
        std::filesystem::remove(FIRMWARE_FILENAME);
        std::filesystem::remove(CHEATS_FILENAME);
        std::filesystem::remove(BOOTLOADER_FILENAME);
        std::filesystem::remove(CHEATS_VERSION);
        std::filesystem::remove(CUSTOM_FILENAME);
        std::filesystem::remove(CFW_FILENAME);
        fs::removeDir(AMS_DIRECTORY_PATH);
        fs::removeDir(SEPT_DIRECTORY_PATH);
        fs::removeDir(FW_DIRECTORY_PATH);
        fs::removeDir(KEFIR_DIRECTORY_PATH);
        return;
    }

    // З логуванням
    std::ofstream logFile(DEBUG_LOG_FILE, std::ios::app);
    logFile << "=== cleanup() START ===" << std::endl;
    logFile << "Timestamp: " << time(nullptr) << std::endl;

    logFile << "Removing: " << AMS_FILENAME << " (exists: " << std::filesystem::exists(AMS_FILENAME) << ")" << std::endl;
    std::filesystem::remove(AMS_FILENAME);

    logFile << "Removing: " << APP_FILENAME_TEMP << " (exists: " << std::filesystem::exists(APP_FILENAME_TEMP) << ")" << std::endl;
    std::filesystem::remove(APP_FILENAME_TEMP);

    logFile << "Removing: " << FIRMWARE_FILENAME << " (exists: " << std::filesystem::exists(FIRMWARE_FILENAME) << ")" << std::endl;
    std::filesystem::remove(FIRMWARE_FILENAME);

    logFile << "Removing: " << CHEATS_FILENAME << " (exists: " << std::filesystem::exists(CHEATS_FILENAME) << ")" << std::endl;
    std::filesystem::remove(CHEATS_FILENAME);

    logFile << "Removing: " << BOOTLOADER_FILENAME << " (exists: " << std::filesystem::exists(BOOTLOADER_FILENAME) << ")" << std::endl;
    std::filesystem::remove(BOOTLOADER_FILENAME);

    logFile << "Removing: " << CHEATS_VERSION << " (exists: " << std::filesystem::exists(CHEATS_VERSION) << ")" << std::endl;
    std::filesystem::remove(CHEATS_VERSION);

    logFile << "Removing: " << CUSTOM_FILENAME << " (exists: " << std::filesystem::exists(CUSTOM_FILENAME) << ")" << std::endl;
    std::filesystem::remove(CUSTOM_FILENAME);

    logFile << "Removing: " << CFW_FILENAME << " (exists: " << std::filesystem::exists(CFW_FILENAME) << ")" << std::endl;
    std::filesystem::remove(CFW_FILENAME);

    logFile << "Removing dir: " << AMS_DIRECTORY_PATH << " (exists: " << std::filesystem::exists(AMS_DIRECTORY_PATH) << ")" << std::endl;
    fs::removeDir(AMS_DIRECTORY_PATH);

    logFile << "Removing dir: " << SEPT_DIRECTORY_PATH << " (exists: " << std::filesystem::exists(SEPT_DIRECTORY_PATH) << ")" << std::endl;
    fs::removeDir(SEPT_DIRECTORY_PATH);

    logFile << "Removing dir: " << FW_DIRECTORY_PATH << " (exists: " << std::filesystem::exists(FW_DIRECTORY_PATH) << ")" << std::endl;
    fs::removeDir(FW_DIRECTORY_PATH);

    logFile << "Removing dir: " << KEFIR_DIRECTORY_PATH << " (exists: " << std::filesystem::exists(KEFIR_DIRECTORY_PATH) << ")" << std::endl;
    fs::removeDir(KEFIR_DIRECTORY_PATH);

    logFile << "=== cleanup() END ===" << std::endl << std::endl;
    logFile.close();
}

void cleanupOnExit()
{
    std::filesystem::remove(APP_FILENAME_TEMP);

    if (util::isDebugLoggingEnabled()) {
        std::ofstream logFile(DEBUG_LOG_FILE, std::ios::app);
        logFile << "=== cleanupOnExit() called ===" << std::endl;
        logFile << "Removed: " << APP_FILENAME_TEMP << std::endl << std::endl;
        logFile.close();
    }
}
