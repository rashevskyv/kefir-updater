#pragma once
constexpr const char ROOT_PATH[]=                   "/";
constexpr const char APP_PATH[] =                   "/switch/kefir-updater/";
constexpr const char NRO_PATH[] =                   "/switch/kefir-updater/kefir-updater.nro";
constexpr const char NRO_PATH_REGEX[] =             ".*(/switch/kefir-updater.*kefir-updater.nro).*";
constexpr const char DOWNLOAD_PATH[] =              "/config/kefir-updater/";
constexpr const char CONFIG_PATH[] =                "/config/kefir-updater/";
constexpr const char CONFIG_PATH_UNZIP[] =          "config\\kefir-updater";
constexpr const char CONFIG_FILE[] =                "/config/kefir-updater/config.json";
constexpr const char DEBUG_LOG_FILE[] =             "/config/kefir-updater/dbi_update.log";

constexpr const char RCM_PAYLOAD_PATH[] =           "/payload.bin";
constexpr const char MARIKO_PAYLOAD_PATH[] =        "/payload.bin";
constexpr const char MARIKO_PAYLOAD_PATH_TEMP[] =   "/payload.bin.aio";

constexpr const char APP_URL[] =                    "https://github.com/rashevskyv/DBI/releases/latest/download/DBI.nro";
constexpr const char TAGS_INFO[] =                  "https://api.github.com/repos/rashevskyv/DBI/releases/latest";
constexpr const char APP_FILENAME[] =               "/switch/DBI/DBI.nro";
constexpr const char APP_FILENAME_TEMP[] =          "/switch/DBI/DBI.nro.tmp";

constexpr const char NXLINKS_URL[] =                "https://raw.githubusercontent.com/rashevskyv/nx-links/master/nx-links.json";
constexpr const char CUSTOM_FILENAME[] =            "/config/kefir-updater/custom.zip";
constexpr const char FIRMWARE_FILENAME[] =          "/config/kefir-updater/firmware.zip";
constexpr const char FIRMWARE_PATH[] =              "/firmware/";
constexpr const char CFW_FILENAME[] =               "/config/kefir-updater/atmo.zip";
constexpr const char BOOTLOADER_FILENAME[] =        "/config/kefir-updater/atmo.zip";

constexpr const char AMS_FILENAME[] =               "/config/kefir-updater/atmo.zip";

constexpr const char HEKATE_URL[] =                 "https://raw.githubusercontent.com/HamletDuFromage/nx-links/master/hekate.json";

constexpr const char DEEPSEA_META_JSON[] =          "https://builder.teamneptune.net/meta.json";
constexpr const char DEEPSEA_BUILD_URL[] =          "https://builder.teamneptune.net/build/";
constexpr const char DEEPSEA_PACKAGE_PATH[] =       "/config/deepsea/customPackage.json";

constexpr const char CUSTOM_PACKS_PATH[] =          "/config/kefir-updater/customPacks.json";

constexpr const char CHEATS_URL_TITLES[] =          "https://github.com/HamletDuFromage/switch-cheats-db/releases/latest/download/titles.zip";
constexpr const char CHEATS_URL_CONTENTS[] =        "https://github.com/HamletDuFromage/switch-cheats-db/releases/latest/download/contents.zip";
constexpr const char GFX_CHEATS_URL_TITLES[] =      "https://github.com/HamletDuFromage/switch-cheats-db/releases/latest/download/titles_60fps-res-gfx.zip";
constexpr const char GFX_CHEATS_URL_CONTENTS[] =    "https://github.com/HamletDuFromage/switch-cheats-db/releases/latest/download/contents_60fps-res-gfx.zip";
constexpr const char CHEATS_URL_VERSION[] =         "https://github.com/HamletDuFromage/switch-cheats-db/releases/latest/download/VERSION";
constexpr const char LOOKUP_TABLE_URL[] =           "https://raw.githubusercontent.com/HamletDuFromage/switch-cheats-db/master/versions.json";
constexpr const char LOOKUP_TABLE_CBOR[] =          "https://github.com/HamletDuFromage/switch-cheats-db/raw/master/versions.cbor";
constexpr const char VERSIONS_DIRECTORY[] =         "https://raw.githubusercontent.com/HamletDuFromage/switch-cheats-db/master/versions/";
constexpr const char CHEATS_DIRECTORY[] =           "https://raw.githubusercontent.com/HamletDuFromage/switch-cheats-db/master/cheats/";
constexpr const char CHEATS_DIRECTORY_GBATEMP[] =   "https://raw.githubusercontent.com/HamletDuFromage/switch-cheats-db/master/cheats_gbatemp/";
constexpr const char CHEATS_DIRECTORY_GFX[] =       "https://raw.githubusercontent.com/HamletDuFromage/switch-cheats-db/master/cheats_gfx/";
constexpr const char CHEATSLIPS_CHEATS_URL[] =      "https://www.cheatslips.com/api/v1/cheats/";
constexpr const char CHEATSLIPS_TOKEN_URL[] =       "https://www.cheatslips.com/api/v1/token";
constexpr const char TOKEN_PATH[] =                 "/config/kefir-updater/token.json";
constexpr const char CHEATS_FILENAME[] =            "/config/kefir-updater/cheats.zip";
constexpr const char CHEATS_EXCLUDE[] =             "/config/kefir-updater/exclude.txt";
constexpr const char FILES_IGNORE[] =               "/config/kefir-updater/preserve.txt";
constexpr const char INTERNET_JSON[] =              "/config/kefir-updater/internet.json";
constexpr const char UPDATED_TITLES_PATH[] =        "/config/kefir-updater/updated.dat";
constexpr const char CHEATS_VERSION[] =             "/config/kefir-updater/cheats_version.dat";
constexpr const char AMS_CONTENTS[] =               "/atmosphere/contents/";
constexpr const char AMS_PATH[] =                   "/atmosphere/";
constexpr const char CONTENTS_PATH[] =              "contents/";
constexpr const char TITLES_PATH[] =                "titles/";
constexpr const char KEFIR_DIRECTORY_PATH[] =       "/kefir/";

constexpr const char COLOR_PICKER_URL[] =           "https://git.io/jcpicker";
constexpr const char JC_COLOR_URL[] =               "https://raw.githubusercontent.com/HamletDuFromage/aio-switch-updater/master/jc_profiles.json";
constexpr const char JC_COLOR_PATH[] =              "/config/kefir-updater/jc_profiles.json";
constexpr const char PC_COLOR_URL[] =               "https://raw.githubusercontent.com/HamletDuFromage/aio-switch-updater/master/pc_profiles.json";
constexpr const char PC_COLOR_PATH[] =              "/config/kefir-updater/pc_profiles.json";

constexpr const char PAYLOAD_PATH[] =               "/payloads/";
constexpr const char BOOTLOADER_PATH[] =            "/bootloader/";
constexpr const char BOOTLOADER_PL_PATH[] =         "/bootloader/payloads/";
constexpr const char UPDATE_BIN_PATH[] =            "/bootloader/update.bin";
constexpr const char REBOOT_PAYLOAD_PATH[] =        "/atmosphere/reboot_payload.bin";
constexpr const char FUSEE_SECONDARY[] =            "/atmosphere/fusee-secondary.bin";
constexpr const char FUSEE_MTC[] =                  "/atmosphere/fusee-mtc.bin";

constexpr const char AMS_DIRECTORY_PATH[] =         "/config/kefir-updater/atmosphere/";
constexpr const char SEPT_DIRECTORY_PATH[] =        "/config/kefir-updater/sept/";
constexpr const char FW_DIRECTORY_PATH[] =          "/firmware/";


constexpr const char HIDE_TABS_JSON[] =             "/config/kefir-updater/hide_tabs.json";
constexpr const char COPY_FILES_TXT[] =             "/config/kefir-updater/copy_files.txt";
constexpr const char LANGUAGE_JSON[] =              "/config/kefir-updater/language.json";
constexpr const char HOMEBREW[] =                   "/config/kefir-updater/language.json";

constexpr const char HIDDEN_AIO_FILE[] =            "/config/kefir-updater/.kefir-updater";

constexpr const char ROMFS_PATH[] =                 "romfs:/";
constexpr const char ROMFS_FORWARDER[] =            "romfs:/aiosu-forwarder.nro";
constexpr const char FORWARDER_PATH[] =             "/config/kefir-updater/aiosu-forwarder.nro";

constexpr const char DAYBREAK_PATH[] =              "/switch/daybreak/daybreak.nro";

constexpr const char LOCALISATION_FILE[] =          "romfs:/i18n/{}/menus.json";

constexpr const int LISTITEM_HEIGHT =               50;

enum class contentType
{
    custom,
    cheats,
    fw,
    app,
    bootloaders,
    ams_cfw,
    payloads,
    hekate_ipl,
};

constexpr std::string_view contentTypeNames[8]{"custom", "cheats", "firmwares", "app", "bootloaders", "cfws", "payloads", "hekate_ipl"};

enum class CFW
{
    rnx,
    sxos,
    ams,
};