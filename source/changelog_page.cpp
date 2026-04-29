#include "changelog_page.hpp"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>
#include "utils.hpp"
#include "fs.hpp"
#include "constants.hpp"

namespace i18n = brls::i18n;
using namespace i18n::literals;
ChangelogPage::ChangelogPage() : AppletFrame(true, true)
{
    this->setTitle("menus/changelog/changelog"_i18n);
    list = new brls::List();
    std::vector<std::string> verTitles;
    std::string change;
    std::vector<std::string> changes;

    verTitles.push_back("v1.0.1");
    changes.push_back("\uE016 Added dialogue box asking about ini files.\n\uE016 Fixed update app link when not connected to the internet.\n\uE016 Minor fixes here and there.");

    verTitles.push_back("v1.0.2");
    changes.push_back("Now prompts the user if they want to replace hetake_ipl.ini.");

    verTitles.push_back("v1.0.3");
    changes.push_back("\uE016 Fixed progress bar sometimes being stuck when extracting.");

    verTitles.push_back("v1.1.0");
    changes.push_back("\uE016 Added an option to download payloads to '/bootloader/payloads'.\n\uE016 Cleaned up some stuff, made .ini overwriting cleaner.\n");

    verTitles.push_back("v1.1.1");
    changes.push_back("\uE016 Added some safety checks before downloading/extracting.\n\uE016 Added the possibility to copy a payload to '/atmosphere/reboot_payload.bin'\n\uE016 Added changelog in 'Tools'\n");

    verTitles.push_back("v1.1.2");
    changes.push_back("\uE016 Added GUI to disable cheat updates for specific titles.");

    verTitles.push_back("v1.1.3");
    changes.push_back("\uE016 Now displays the latest installed cheat version.\n\uE016 Now warns in the app title if a new update is available.");

    verTitles.push_back("v1.2.3");
    changes.push_back("\uE016 Now multilingual (credits to github.com/tiansongyu).\n\uE016 Chinese and French are currently supported.");

    verTitles.push_back("v1.2.1");
    changes.push_back("\uE016 Added option to set a payload to /bootloader/update.bin");

    verTitles.push_back("v1.2.2");
    changes.push_back("\uE016 Added Japanese localisation (credits to github.com/yyoossk).");

    verTitles.push_back("v1.2.4");
    changes.push_back("\uE016 Fixed app self-update");

    verTitles.push_back("v1.2.5");
    changes.push_back("\uE016 Improved Japanese translation");

    verTitles.push_back("v1.2.6");
    changes.push_back("\uE016 Added spanish translation (credits to github.com/sergiou87");

    verTitles.push_back("v1.3.0");
    changes.push_back("\uE016 Added back the ability to update CFWs");

    verTitles.push_back("v1.3.1");
    changes.push_back("\uE016 Small fixes for bugs causing hangs.");

    verTitles.push_back("v1.3.2");
    changes.push_back("\uE016 Added ability to change the internet color of Pro Controllers.\n\uE016 Added the ability to preserve specific files when updating.\n\uE016 Added the ability to clean up downloaded archives.");

    verTitles.push_back("v1.4.0");
    changes.push_back("\uE016 Added possibility to use pre-set network settings. Add your own in `config/aio-switch-updater/internet.json.\n\uE016 Added web browser.");

    verTitles.push_back("v1.4.1");
    changes.push_back("\uE016 Fixed misleading display in internet settings page.");

    verTitles.push_back("v1.4.2");
    changes.push_back("\uE016 (hopefully) fixed unreliable copy of payloads.");

    verTitles.push_back("v1.4.3");
    changes.push_back("\uE016 Fixed switch not rebooting to hekate payload after updating.");

    verTitles.push_back("v1.5.0");
    changes.push_back("\uE016 Overhauled the app update feature.");

    verTitles.push_back("v1.5.1");
    changes.push_back("\uE016 A few graphical tweaks.");

    verTitles.push_back("v1.5.2");
    changes.push_back("\uE016 Added support for Traditional Chinese (credits to github.com/qazrfv1234)");

    verTitles.push_back("v2.0.0");
    changes.push_back("\uE016 Added ability to download cheatslips cheats.\n\uE016 Added way to toggle out tabs.\n\uE016 Various code improvements.");

    verTitles.push_back("v2.0.1");
    changes.push_back("\uE016 Fixed a bug not letting the user click no when asked if they want to install hekate.\n\uE016 Correct a bunch of typos.");

    verTitles.push_back("v2.1.0");
    changes.push_back("\uE016 Switched to a better way to get links.");

    verTitles.push_back("v2.1.1");
    changes.push_back("\uE016 Changed the cheatslips cheatsheet view.");

    verTitles.push_back("v2.1.2");
    changes.push_back("\uE016 Fixed wronge hekate link.");

    verTitles.push_back("v2.2.0");
    changes.push_back("\uE016 For cheatslips.com, the build ID of a running game will now be fetched, allowing you to access cheatsheets even if the build ID isn't listed in the versions database.");

    verTitles.push_back("v2.2.1");
    changes.push_back("\uE016 Fixed non Atmosphere CFW being wrongly categorised as ams.");

    verTitles.push_back("v2.3.0");
    changes.push_back("\uE016 Added possibility to copy a list of files to custom locations. This may come in handy for trinket/esoteric bootloader users.\n\uE016 Added warning screen on launch.\n\uE016 Few UI tweaks.\n\uE016 Traditional Chinese translation updated (qazrfv1234)");

    verTitles.push_back("v2.3.1");
    changes.push_back("\uE016 Files for batch copy are now copied according to the json order (formerly alphabetical order).");

    verTitles.push_back("v2.3.2");
    changes.push_back("\uE016 Fixed batch copy not copying :^)");

    verTitles.push_back("v2.3.3");
    changes.push_back("\uE016 Hide unsupported features for Mariko Switches");

    verTitles.push_back("v2.3.4");
    changes.push_back("\uE016 Minor fixes, refactored old switch-cheats updater code and changed way to detect CFW");

    verTitles.push_back("v2.4.0");
    changes.push_back("\uE016 Added option to extract the entire gbatemp cheats archive.\n\uE016 Shortened load times.\n\uE016 Added German localisation (credits to github.com/Slluxx).\n\uE016 Added option to disable sysmodules prior to updating.\n\uE016 Improved Japanese localisation (credits to github.com/yyoossk).\n\uE016 Added current AMS version display.");

    verTitles.push_back("v2.4.1");
    changes.push_back("\uE016 Added information about download progress.");

    verTitles.push_back("v2.4.2");
    changes.push_back("\uE016 Added option to manually change language.\n\uE016 Fixed broken strings.\n\uE016 Few visual tweaks.");

    verTitles.push_back("v2.4.3");
    changes.push_back("\uE016 Added way to select system default in language selection.\n\uE016 Display local IP in internet settings.\n\uE016 Added Polish localisation (credits to github.com/teddy74eva).\n\uE016 Updated Traditional Chinese localisation (credits to https://github.com/qazrfv1234).\n\uE016 Minor code changes.");

    verTitles.push_back("v2.4.4");
    changes.push_back("\uE016 Significantly reduced time to retrieve build IDs.\n\uE016 Updated Polish localisation (credits to github.com/teddy74eva).");

    verTitles.push_back("v2.4.5-fix_ams");
    changes.push_back("\uE016 Atmosphère 0.19+ support. Note that this version assumes your switch is running Atmosphère. I should fix this soon, but if you're on SXOS, please stay on 2.4.4.");

    verTitles.push_back("v2.4.6");
    changes.push_back("\uE016 Added back support for SXOS.\n\uE016 Removed dialogue asking to update Hekate if downloading DeepSea.\n\uE016 Fixed incorrect description in inject payload menu.");

    verTitles.push_back("v2.4.7");
    changes.push_back("\uE016 Fixed app only working on 0.19 AMS.\n\uE016 Proper replacement of stratosphere.romfs when updating.");

    verTitles.push_back("v2.4.8");
    changes.push_back("\uE016 Fixed crashes when trying to focus empty lists (typically when in airplane mode).");

    verTitles.push_back("v2.4.9");
    changes.push_back("\uE016 Fixed some read-only files not being properly extracted thus preventing updating.");

    verTitles.push_back("v2.5.0");
    changes.push_back("\uE016 Added ability to update Atmosphère for Mariko (ie patched) Switches. Thanks to SkyDark for testing it out.\n\uE016 Fixed batch copy to be able to copy the same file multiple times (see https://git.io/aiosu_copyfiles). Existing copy_files.json files won't work anymore.");

    verTitles.push_back("v2.5.1");
    changes.push_back("\uE016 Fixed bug copying Mariko payloads on Erista.");

    verTitles.push_back("v2.5.2");
    changes.push_back("\uE016 Updated Japanese and Traditional Chinese translations (credits to github.com/yyoossk and github.com/qazrfv1234).\n\uE016 Updated payload so that it doesn't throw errors if the bootloader folder is missing.\n\uE016 Minor code changes that may or may not result in performace improvements.");

    verTitles.push_back("v2.5.3");
    changes.push_back("\uE016 Check available size before downloading and extracting files.\n\uE016 Now displaying a message when the custom payload is running.");

    verTitles.push_back("v2.6.0");
    changes.push_back("\uE016 Added ability to download individual cheat codes from the GBAtemp.net archive.\n\uE016 Updated Polish translation (credits to github.com/teddy74eva).");

    verTitles.push_back("v2.6.1");
    changes.push_back("\uE016 Added a safer way to inject payloads (should prevent corruption on exFAT system, not that you should be using exFAT)");

    verTitles.push_back("v2.7.0");
    changes.push_back("\uE016 Fixed Atmosphère updates failing when updating from a system without stratosphere.romfs present on the SD card.\n\uE016 Disabled the option to download individual cheat codes while in applet mode, except for the one game currently running.\n\uE016 UI tweaks.\n\uE016 Prevents crashes when requesting invalid CheatSlips cheat sheets.");

    verTitles.push_back("v2.8.0");
    changes.push_back("\uE016 Restored and improved \"View installed cheats\" menu. You can now browse the content of your cheatsheets from the app.");

    verTitles.push_back("v2.9.0");
    changes.push_back("\uE016 Added support for Team-Neptune's custom pack builder.");

    verTitles.push_back("v2.10.0");
    changes.push_back("\uE016 Added support custom packs through a json file.");

    verTitles.push_back("v2.10.1");
    changes.push_back("\uE016 Fixed crashes in airplane mode introduced in 2.10.0");

    verTitles.push_back("v2.11.0");
    changes.push_back("\uE016 Borealis changes for visual tweaks (tickering labels, scroll bar etc).\n\uE016 When needed, issue a warning about custom themes after downloading a new firmware.\n\uE016 Abort AMS update process for Mariko Switches when payload.bin cannot be found.");

    verTitles.push_back("v2.11.1");
    changes.push_back("\uE016 Added ability to view existing cheats when downloading cheat codes/sheets.\n\uE016 Fixed wrong tid for theme detection.");

    verTitles.push_back("v2.11.2");
    changes.push_back("\uE016 Fixed crash when downloading cheats in applet mode.\n\uE016 Fixed progress bar percentage not showing past 10%.");

    verTitles.push_back("v2.11.3");
    changes.push_back("\uE016 Don't download the cheat archive when already cached.\n\uE016 Added ability to hide more entries through hide_tabs.json.\n\uE016 Better support for non-UTF-8 characters.");

    verTitles.push_back("v2.11.4");
    changes.push_back("\uE016 Fix Traditional Chinese strings not showing.\n\uE016 Remove full RAM access check for firmware downloads.");

    verTitles.push_back("v2.11.5");
    changes.push_back("\uE016 Update Japanese translation.\n\uE016 Do not show theme warning when downloading something that is not firmware files.");

    verTitles.push_back("v2.12.0");
    changes.push_back("\uE016 Prepare for AMS 1.0.0.\n\uE016 Updated Japanese and French translations.\n\uE016 Small bugfixes.");

    verTitles.push_back("v2.12.1");
    changes.push_back("\uE016 Fix crashes in exclude page.");

    verTitles.push_back("v2.13.0");
    changes.push_back("\uE016 Added option to delete all cheat files for a specific game.\n\uE016 Now blocks the home menu during downloads/extraction, and add an option to cancel it.\n\uE016 Updated traditional Chinese translations.");

    verTitles.push_back("v2.14.0");
    changes.push_back("\uE016 Add option to launch Daybreak after downloading a sysupdate.\n\uE016 Download all links at once to cut down on boot times.\n\uE016 Randomize IPs for lan-play in the internet settings page.\n\uE016 Fix default color scheme for pro-cons.");

    verTitles.push_back("v2.15.0");
    changes.push_back("\uE016 Implement cheat codes support for multi-content games.\n\uE016 Move payload downloads to bootloader tab.");

    verTitles.push_back("v2.16.0");
    changes.push_back("\uE016 Ask user about replacing reboot_payload.bin with hekate when updating hekate.\n\uE016 Added option to deleted orphaned cheats.\n\uE016 UX tweaks.");

    verTitles.push_back("v2.16.1");
    changes.push_back("\uE016 Updated Japanese localisation (https://github.com/yyoossk).\n\uE016 Updated German localisation (https://github.com/MSco).\n\uE016 Added ability to manually launch aiosu_rcm.bin.");

    verTitles.push_back("v2.16.2");
    changes.push_back("\uE016 Allow offline extraction of cheats.\n\uE016 Fixed extraction of the the complete cheat archive.\n\uE016 Fixed display bug for cheats extraction.");

    verTitles.push_back("v2.16.3");
    changes.push_back("\uE016 Fetch default profiles online for joy-con and pro-con color swaps.\n\uE016 Updated French localization (https://github.com/NotaInutilis).");

    verTitles.push_back("v2.17.0");
    changes.push_back("\uE016 Add ability to download a basic hekate_ipl file.\n\uE016 Add error messages when cheats are not found for a game.");

    verTitles.push_back("v2.17.1");
    changes.push_back("\uE016 Add disclaimer when cheat codes are found for a different game version.\n\uE016 Improve French and Japanese localization.");

    verTitles.push_back("v2.18.0");
    changes.push_back("\uE016 Add mega.nz support (https://github.com/aedalzotto).\n\uE016 Add Korean localization (https://github.com/DDinghoya).\n\uE016 Improve Spanish localization (https://github.com/Armi-Heavy).");

    verTitles.push_back("v2.18.1");
    changes.push_back("\uE016 Fix some pop-up related bugs.");

    verTitles.push_back("v2.19.0");
    changes.push_back("\uE016 Added ability to view games with missing updates.\n\uE016 Updated Japanese localisation (https://github.com/yyoossk).\n\uE016 Updated Chinese localisation (https://github.com/Physton).");

    verTitles.push_back("v2.19.1");
    changes.push_back("\uE016 Fixed crash when trying to download cheats in applet mode.\n\uE016 Updated Japanese localisation (https://github.com/yyoossk).\n\uE016 Updated Chinese localisation (https://github.com/qazrfv1234).");

    verTitles.push_back("v2.19.2");
    changes.push_back("\uE016 Fixed Japanese locale.");

    verTitles.push_back("v2.19.3");
    changes.push_back("\uE016 Fix wrong bid for titles overriden by HBL.\n\uE016 Improve Korean localisation (https://github.com/DDinghoya).\n\uE016 Improve Italian localisation (https://github.com/clamintus).");

    verTitles.push_back("v2.20.0");
    changes.push_back("\uE016 Significantly increase extraction speed (https://github.com/PoloNX).\n\uE016 Create a \"Custom Downloads\" tab that supports user-provided links for Atmosphère packs as well as regular downloads.");

    verTitles.push_back("v2.20.1");
    changes.push_back("\uE016 Fix crashes on plane mode.\n\uE016 Account for carriage returns in preserve.txt.");

    verTitles.push_back("v2.21.0");
    changes.push_back("\uE016 Managing custom download links is now possible directly from the app.\n\uE016 Toggle/untoggle all games in cheats menu->exclude games from receiving cheat updates.");

    verTitles.push_back("v2.21.0");
    changes.push_back("\uE016 Dialogs now default to not overwriting .ini files");

    verTitles.push_back("v2.21.2");
    changes.push_back("\uE016 Improved Korean translation.\n\uE016 Be more conservative when checking available space before a download.\n\uE016 Minor fixes.");

    verTitles.push_back("v2.21.3");
    changes.push_back("\uE016 Added download link for graphic enhancing codes.");


    for (int i = verTitles.size() - 1; i >= 0; i--) {
        listItem = new brls::ListItem(verTitles[i]);
        change = changes[i];
        listItem->getClickEvent()->subscribe([change](brls::View* view) {
            util::showDialogBoxInfo(change);
        });
        list->addView(listItem);
    }
    this->setContentView(list);
}

void ChangelogPage::ShowChangelogContent(const std::string version, const std::string content)
{
    listItem = new brls::ListItem(version);
    listItem->getClickEvent()->subscribe([version, content](brls::View* view) {
        brls::AppletFrame* appView = new brls::AppletFrame(true, true);

        brls::PopupFrame::open(version, appView, "", "");
    });
    list->addView(listItem);
}

// =====================================================================
// Changelog helpers
// =====================================================================

// ---- RichTextLabel -------------------------------------------------
// A custom View that renders a string with inline **bold** support.
// Since borealis FontStash has only one font face (NX shared font),
// bold is simulated by drawing each glyph twice with a 0.5 px x-offset.
class RichTextLabel : public brls::View
{
    enum class Color { Normal, Gray, Red, Blue };
    struct Seg { std::string text; bool bold; Color color; };
    std::vector<Seg> segs;
    float fontSize = 0.0f; // 0 = use style default

    void parse(const std::string& richText)
    {
        bool isBold = false;
        Color currentColor = Color::Normal;
        std::string cur;

        for (size_t i = 0; i < richText.size(); ) {
            // Check for `text` FIRST - everything inside is gray (monospace style)
            // Process backticks BEFORE brackets so [] inside backticks stays gray
            if (richText[i] == '`') {
                if (!cur.empty()) { segs.push_back({cur, isBold, currentColor}); cur.clear(); }

                size_t end = richText.find('`', i + 1);
                if (end != std::string::npos) {
                    // Opening backtick (white)
                    segs.push_back({"`", false, Color::Normal});
                    // Content between backticks is gray
                    std::string backtickContent = richText.substr(i + 1, end - i - 1);
                    segs.push_back({backtickContent, false, Color::Gray});
                    // Closing backtick (white)
                    segs.push_back({"`", false, Color::Normal});
                    i = end + 1;
                } else {
                    cur += richText[i++];
                }
            }
            // Check for **bold**
            else if (i + 1 < richText.size() && richText[i] == '*' && richText[i+1] == '*') {
                if (!cur.empty()) { segs.push_back({cur, isBold, currentColor}); cur.clear(); }
                isBold = !isBold;
                i += 2;
            }
            // Check for URLs: http:// or https://
            else if ((i + 7 <= richText.size() && richText.substr(i, 7) == "http://") ||
                     (i + 8 <= richText.size() && richText.substr(i, 8) == "https://")) {
                if (!cur.empty()) { segs.push_back({cur, isBold, currentColor}); cur.clear(); }

                // Find end of URL (space, newline, or end of string)
                size_t urlEnd = i;
                while (urlEnd < richText.size() &&
                       richText[urlEnd] != ' ' &&
                       richText[urlEnd] != '\n' &&
                       richText[urlEnd] != '\t') {
                    urlEnd++;
                }

                std::string url = richText.substr(i, urlEnd - i);
                segs.push_back({url, isBold, Color::Blue});
                i = urlEnd;
            }
            // Check for [text](url) - markdown link (blue color)
            // or [text] - brackets white, content inside is gray (but can be bold too)
            else if (richText[i] == '[') {
                if (!cur.empty()) { segs.push_back({cur, isBold, currentColor}); cur.clear(); }

                // Find matching ] while skipping content inside backticks
                size_t end = std::string::npos;
                size_t j = i + 1;
                while (j < richText.size()) {
                    if (richText[j] == '`') {
                        // Skip to closing backtick
                        size_t backEnd = richText.find('`', j + 1);
                        if (backEnd != std::string::npos) {
                            j = backEnd + 1;
                        } else {
                            j++;
                        }
                    } else if (richText[j] == ']') {
                        end = j;
                        break;
                    } else {
                        j++;
                    }
                }

                if (end != std::string::npos) {
                    // Check if this is a markdown link [text](url)
                    if (end + 1 < richText.size() && richText[end + 1] == '(') {
                        size_t urlEnd = richText.find(')', end + 2);
                        if (urlEnd != std::string::npos) {
                            // This is a markdown link - render text in blue
                            std::string linkText = richText.substr(i + 1, end - i - 1);

                            // Parse link text with ** support, but force blue color
                            bool innerBold = false;
                            std::string innerCur;
                            for (size_t j = 0; j < linkText.size(); ) {
                                if (j + 1 < linkText.size() && linkText[j] == '*' && linkText[j+1] == '*') {
                                    if (!innerCur.empty()) {
                                        segs.push_back({innerCur, innerBold, Color::Blue});
                                        innerCur.clear();
                                    }
                                    innerBold = !innerBold;
                                    j += 2;
                                } else {
                                    innerCur += linkText[j++];
                                }
                            }
                            if (!innerCur.empty()) segs.push_back({innerCur, innerBold, Color::Blue});

                            i = urlEnd + 1; // Skip the entire [text](url)
                            continue;
                        }
                    }

                    // Not a markdown link - treat as regular [text] with gray content
                    // Add opening bracket (normal color, not gray)
                    segs.push_back({"[", false, Color::Normal});

                    // Parse content with ** and `` support, but force gray color
                    std::string bracketContent = richText.substr(i + 1, end - i - 1);
                    bool innerBold = false;
                    std::string innerCur;
                    for (size_t j = 0; j < bracketContent.size(); ) {
                        // Check for backticks inside brackets
                        if (bracketContent[j] == '`') {
                            if (!innerCur.empty()) {
                                segs.push_back({innerCur, innerBold, Color::Gray});
                                innerCur.clear();
                            }
                            size_t backEnd = bracketContent.find('`', j + 1);
                            if (backEnd != std::string::npos) {
                                // Opening backtick (white)
                                segs.push_back({"`", false, Color::Normal});
                                // Content is gray
                                std::string backContent = bracketContent.substr(j + 1, backEnd - j - 1);
                                segs.push_back({backContent, false, Color::Gray});
                                // Closing backtick (white)
                                segs.push_back({"`", false, Color::Normal});
                                j = backEnd + 1;
                            } else {
                                innerCur += bracketContent[j++];
                            }
                        }
                        else if (j + 1 < bracketContent.size() && bracketContent[j] == '*' && bracketContent[j+1] == '*') {
                            if (!innerCur.empty()) {
                                segs.push_back({innerCur, innerBold, Color::Gray});
                                innerCur.clear();
                            }
                            innerBold = !innerBold;
                            j += 2;
                        } else {
                            innerCur += bracketContent[j++];
                        }
                    }
                    if (!innerCur.empty()) segs.push_back({innerCur, innerBold, Color::Gray});

                    // Add closing bracket (normal color, not gray)
                    segs.push_back({"]", false, Color::Normal});

                    i = end + 1;
                } else {
                    cur += richText[i++];
                }
            }
            // Check for 'text' at word start - everything inside is gray
            else if (richText[i] == '\'' && (i == 0 || richText[i-1] == ' ' || richText[i-1] == '\n' || richText[i-1] == '\t')) {
                if (!cur.empty()) { segs.push_back({cur, isBold, currentColor}); cur.clear(); }

                size_t end = richText.find('\'', i + 1);
                if (end != std::string::npos) {
                    // Add opening quote (white)
                    segs.push_back({"'", false, Color::Normal});
                    // Add content (gray, can be bold)
                    std::string quoteContent = richText.substr(i + 1, end - i - 1);
                    bool innerBold = false;
                    std::string innerCur;
                    for (size_t j = 0; j < quoteContent.size(); ) {
                        if (j + 1 < quoteContent.size() && quoteContent[j] == '*' && quoteContent[j+1] == '*') {
                            if (!innerCur.empty()) {
                                segs.push_back({innerCur, innerBold, Color::Gray});
                                innerCur.clear();
                            }
                            innerBold = !innerBold;
                            j += 2;
                        } else {
                            innerCur += quoteContent[j++];
                        }
                    }
                    if (!innerCur.empty()) segs.push_back({innerCur, innerBold, Color::Gray});
                    // Add closing quote (white)
                    segs.push_back({"'", false, Color::Normal});

                    i = end + 1;
                } else {
                    cur += richText[i++];
                }
            }
            // Check for {{red}}text{{/red}}
            else if (i + 6 < richText.size() && richText.substr(i, 7) == "{{red}}") {
                if (!cur.empty()) { segs.push_back({cur, isBold, currentColor}); cur.clear(); }
                size_t end = richText.find("{{/red}}", i + 7);
                if (end != std::string::npos) {
                    std::string redText = richText.substr(i + 7, end - i - 7);
                    segs.push_back({redText, isBold, Color::Red});
                    i = end + 8;
                } else {
                    cur += richText[i++];
                }
            }
            // Check for {{blue}}text{{/blue}}
            else if (i + 7 < richText.size() && richText.substr(i, 8) == "{{blue}}") {
                if (!cur.empty()) { segs.push_back({cur, isBold, currentColor}); cur.clear(); }
                size_t end = richText.find("{{/blue}}", i + 8);
                if (end != std::string::npos) {
                    std::string blueText = richText.substr(i + 8, end - i - 8);
                    segs.push_back({blueText, isBold, Color::Blue});
                    i = end + 9;
                } else {
                    cur += richText[i++];
                }
            }
            else {
                cur += richText[i++];
            }
        }
        if (!cur.empty()) segs.push_back({cur, isBold, currentColor});
    }

    // Word-wrap pass. Returns total rendered height.
    // doRender=false → measure only; doRender=true → draw.
    float wrapPass(NVGcontext* vg, float bx, float by, float vw,
                   float fsz, float pixLineH, int font,
                   NVGcolor normalColor, bool doRender)
    {
        nvgFontFaceId(vg, font);
        nvgFontSize(vg, fsz);
        nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);

        // nvgTextBounds(" ") returns 0 because spaces have no visual extent in NVG.
        // Measure the actual advance by subtracting "ab" width from "a b" width.
        float wAB[4], wA_B[4];
        nvgTextBounds(vg, 0, 0, "ab",  nullptr, wAB);
        nvgTextBounds(vg, 0, 0, "a b", nullptr, wA_B);
        float spaceW = (wA_B[2] - wA_B[0]) - (wAB[2] - wAB[0]);
        if (spaceW < 1.0f) spaceW = fsz * 0.28f; // fallback (~1/3 em)

        float curX = bx, curY = by;
        bool lineStart = true;
        bool needsSpace = false;
        std::string wordBuf;
        bool wordBold = false;
        Color wordColor = Color::Normal;

        auto flushWord = [&]() {
            if (wordBuf.empty()) return;

            float bounds[4];
            nvgFontFaceId(vg, font);
            nvgFontSize(vg, fsz);
            nvgTextBounds(vg, 0, 0, wordBuf.c_str(), nullptr, bounds);
            float ww = bounds[2] - bounds[0];
            float boldExtra = wordBold ? 1.0f : 0.0f;
            float sw = needsSpace ? spaceW : 0.0f;

            // Wrap if word doesn't fit
            if (!lineStart && curX + sw + ww + boldExtra > bx + vw) {
                curX = bx;
                curY += pixLineH;
                lineStart = true;
                sw = 0.0f;
            }

            if (doRender && !lineStart && sw > 0.0f) {
                nvgFillColor(vg, normalColor);
                nvgText(vg, curX, curY, " ", nullptr);
            }
            curX += sw;

            if (doRender) {
                // Set color based on wordColor
                NVGcolor drawColor = normalColor;
                if (wordColor == Color::Gray) {
                    drawColor = nvgRGBA(128, 128, 128, 255); // Gray
                } else if (wordColor == Color::Red) {
                    drawColor = nvgRGBA(255, 80, 80, 255); // Red
                } else if (wordColor == Color::Blue) {
                    drawColor = nvgRGBA(100, 150, 255, 255); // Light blue (link color)
                }
                nvgFillColor(vg, drawColor);

                nvgFontFaceId(vg, font);
                nvgFontSize(vg, fsz);
                nvgText(vg, curX, curY, wordBuf.c_str(), nullptr);
                if (wordBold) // bold simulation: second draw shifted 1.0 px
                    nvgText(vg, curX + 1.0f, curY, wordBuf.c_str(), nullptr);
            }

            curX += ww + boldExtra;
            lineStart = false;
            needsSpace = false;
            wordBuf.clear();
        };

        for (auto& seg : segs) {
            wordBold = seg.bold;
            wordColor = seg.color;
            for (char c : seg.text) {
                if (c == '\n') {
                    flushWord();
                    needsSpace = false;
                    curX = bx;
                    curY += pixLineH;
                    lineStart = true;
                } else if (c == ' ') {
                    flushWord();
                    if (!lineStart) needsSpace = true;
                } else {
                    wordBuf += c;
                }
            }
            flushWord(); // flush at ** boundary (no space injected)
        }

        return (curY - by) + pixLineH;
    }

public:
    RichTextLabel(const std::string& richText, float fontSize = 0.0f) : fontSize(fontSize) { parse(richText); }

    void layout(NVGcontext* vg, brls::Style* style, brls::FontStash* stash) override
    {
        if (this->width == 0 || segs.empty()) { this->height = 0; return; }

        float fsz = (fontSize > 0.0f) ? fontSize : (float)style->Label.regularFontSize;
        float pixLineH = fsz * style->Label.lineHeight;

        nvgSave(vg);
        nvgReset(vg);

        float h = wrapPass(vg, 0.0f, 0.0f, (float)this->width,
                           fsz, pixLineH, stash->regular, {}, false);
        this->height = (unsigned)std::ceil(h);
        nvgRestore(vg);
    }

    void draw(NVGcontext* vg, int x, int y, unsigned width, unsigned /*height*/,
              brls::Style* style, brls::FrameContext* ctx) override
    {
        if (segs.empty()) return;

        float fsz = (fontSize > 0.0f) ? fontSize : (float)style->Label.regularFontSize;
        float pixLineH = fsz * style->Label.lineHeight;
        NVGcolor color = a(ctx->theme->textColor);

        nvgSave(vg);
        wrapPass(vg, (float)x, (float)y, (float)width,
                 fsz, pixLineH, ctx->fontStash->regular, color, true);
        nvgRestore(vg);
    }
};
// ---- End RichTextLabel ---------------------------------------------

// Returns true when the app UI is set to Ukrainian
static bool isUkrainianLocale()
{
    nlohmann::json langFile = fs::parseJsonFile(LANGUAGE_JSON);
    if (langFile.find("language") != langFile.end()) {
        std::string lang = langFile["language"].get<std::string>();
        return lang == "ua" || lang == "uk";
    }
    std::string locale = brls::i18n::getCurrentLocale();
    return locale == "uk" || locale == "ua";
}

// Extracts UKR or ENG section from a raw changelog file.
static std::string extractChangelogSection(const std::string& raw, bool ukrainian)
{
    const std::string urkHeader = "#### **UKR**";
    const std::string engHeader = "#### **ENG**";
    const std::string separator = "____";

    if (ukrainian) {
        size_t pos = raw.find(urkHeader);
        if (pos == std::string::npos) return raw;
        size_t start = pos + urkHeader.size();
        size_t sepPos = raw.find(separator, start);
        return raw.substr(start, (sepPos != std::string::npos ? sepPos : raw.size()) - start);
    } else {
        size_t pos = raw.find(engHeader);
        if (pos == std::string::npos) return raw;
        return raw.substr(pos + engHeader.size());
    }
}

// Process markdown links: [visible](url) → {{blue}}visible{{/blue}}
static std::string processMarkdownLinks(const std::string& text)
{
    std::string result;
    result.reserve(text.size());
    for (size_t i = 0; i < text.size(); ) {
        if (text[i] == '[') {
            size_t closeB = text.find(']', i + 1);
            if (closeB != std::string::npos && closeB + 1 < text.size() && text[closeB+1] == '(') {
                size_t closeP = text.find(')', closeB + 2);
                if (closeP != std::string::npos) {
                    // This is a markdown link - wrap text in {{blue}}
                    std::string linkText = text.substr(i + 1, closeB - i - 1);
                    result += "{{blue}}" + linkText + "{{/blue}}";
                    i = closeP + 1;
                    continue;
                }
            }
        }
        result += text[i++];
    }
    return result;
}

// Process markdown links: [visible](url) → keep as is for parse() to handle
// Remove backticks from code spans
static std::string processMarkdown(const std::string& text)
{
    // Just return as-is, parse() will handle [text](url) links
    return text;
}

// Returns true when trimmed line is entirely bold: **content**
static bool isFullBoldLine(const std::string& trimmed)
{
    return trimmed.size() >= 5
        && trimmed[0] == '*' && trimmed[1] == '*'
        && trimmed[trimmed.size()-1] == '*' && trimmed[trimmed.size()-2] == '*';
}

// Extract ONLY the changelog entries for version `ver` from a language section.
// Version blocks are delimited by full-bold integer lines like **814**.
// Non-version bold lines (summaries like **Full support 22.1.0**) are included
// only when they appear before the first version-number marker (preamble) AND
// the entire target version was found; otherwise they are also shown as-is.

// Build a rich-text string for RichTextLabel from a filtered version section.
// **bold** markers are PRESERVED; markdown links are stripped; backticks removed;
// bullets converted to •; blank lines removed.
// addBullets: if true, adds 5 non-breaking spaces + bullet before each line
static std::string buildRichText(const std::string& section, bool addBullets)
{
    std::istringstream stream(section);
    std::string line;
    std::string result;
    bool firstLine = true;

    while (std::getline(stream, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();

        size_t ns = line.find_first_not_of(" \t");
        if (ns == std::string::npos) continue; // skip blank lines
        std::string trimmed = line.substr(ns);

        // Skip global headers (## / ####)
        if (trimmed.size() >= 2 && trimmed[0] == '#' && trimmed[1] == '#') continue;
        // Skip separator lines (all underscores or all dashes)
        if (!trimmed.empty() && trimmed.find_first_not_of('_') == std::string::npos) continue;
        if (trimmed.size() >= 3 && trimmed.find_first_not_of('-') == std::string::npos) continue;

        // Indent for nested bullets
        std::string indentStr;
        for (size_t i = 0; i < ns; i++)
            indentStr += (line[i] == '\t') ? "    " : " ";

        // Process markdown links: [text](url) → {{blue}}text{{/blue}}
        std::string processed = processMarkdownLinks(trimmed);

        // Keep ** bold markers; remove bare single * (italic)
        {
            std::string out;
            for (size_t i = 0; i < processed.size(); ) {
                if (processed[i] == '*') {
                    if (i + 1 < processed.size() && processed[i+1] == '*') {
                        out += "**"; i += 2; // keep bold markers
                    } else {
                        i++; // drop single * italic
                    }
                } else {
                    out += processed[i++];
                }
            }
            processed = out;
        }

        if (!firstLine) result += '\n';
        if (addBullets) {
            result += "\u00A0\u00A0\u00A0\u00A0\u00A0\u2022 " + indentStr + processed;
        } else {
            result += indentStr + processed;
        }
        firstLine = false;
    }
    return result;
}

// =====================================================================
// ChangelogPage_Kefir implementation
ChangelogPage_Kefir::ChangelogPage_Kefir(brls::StagedAppletFrame* frame, const std::string& currentVersion, const std::string& targetVersion, const std::string& url)
{
    // Log debug info
    std::ofstream logFile("/config/kefir-updater/changelog_debug.log", std::ios::app);
    logFile << "=== ChangelogPage_Kefir Debug ===" << std::endl;
    logFile << "Current version raw: " << currentVersion << std::endl;
    logFile << "Target version raw: " << targetVersion << std::endl;

    // Create warning label
    this->warningLabel = new brls::Label(
        brls::LabelStyle::REGULAR,
        "menus/changelog/review_before_update"_i18n,
        true
    );
    this->warningLabel->setHorizontalAlign(NVG_ALIGN_CENTER);
    this->warningLabel->setParent(this);

    // Create changelog list
    this->changelogList = new brls::List();
    this->changelogList->setParent(this);

    // Parse versions
    int currentVer = parseKefirVersion(currentVersion);
    int targetVer  = parseKefirVersion(targetVersion);

    logFile << "Parsed current: " << currentVer << std::endl;
    logFile << "Parsed target: " << targetVer << std::endl;

    if (targetVer == 0) {
        auto* errorLabel = new brls::Label(brls::LabelStyle::DESCRIPTION, "Could not determine target version.", true);
        this->changelogList->addView(errorLabel);
        logFile << "ERROR: Target version is 0" << std::endl;
    } else {
        // Download the full changelog file
        std::string changelogUrl = "https://raw.githubusercontent.com/rashevskyv/kefir/master/changelog_full";
        logFile << "Downloading: " << changelogUrl << std::endl;

        std::string changelogText = util::downloadFileToString(changelogUrl);
        logFile << "Got " << changelogText.length() << " bytes" << std::endl;

        if (changelogText.empty()) {
            auto* errorLabel = new brls::Label(brls::LabelStyle::DESCRIPTION, "Failed to download changelog.", true);
            this->changelogList->addView(errorLabel);
            logFile << "ERROR: Failed to download" << std::endl;
        } else {
            // Extract language section
            bool ukrainian = isUkrainianLocale();
            std::string section = extractChangelogSection(changelogText, ukrainian);
            logFile << "Language: " << (ukrainian ? "ua" : "en") << ", section len: " << section.length() << std::endl;

            // Parse the section into preamble + version blocks
            std::string preamble;
            std::vector<std::pair<int, std::string>> versionBlocks;

            std::istringstream stream(section);
            std::string line;
            bool inPreamble = true;
            int currentBlock = -1;
            std::string blockContent;

            while (std::getline(stream, line)) {
                if (!line.empty() && line.back() == '\r') line.pop_back();

                size_t ns = line.find_first_not_of(" \t");
                if (ns == std::string::npos) continue;
                std::string trimmed = line.substr(ns);

                // Check if this is a version marker: **814**
                if (isFullBoldLine(trimmed)) {
                    std::string content = trimmed.substr(2, trimmed.size() - 4);
                    bool isVerNum = !content.empty() && std::all_of(content.begin(), content.end(), ::isdigit);

                    if (isVerNum) {
                        // Save previous block
                        if (currentBlock != -1 && !blockContent.empty()) {
                            versionBlocks.push_back({currentBlock, blockContent});
                        }

                        inPreamble = false;
                        currentBlock = std::stoi(content);
                        blockContent.clear();
                        continue;
                    }
                }

                // Add line to current section
                if (inPreamble) {
                    preamble += line + "\n";
                } else if (currentBlock != -1) {
                    blockContent += line + "\n";
                }
            }

            // Save last block
            if (currentBlock != -1 && !blockContent.empty()) {
                versionBlocks.push_back({currentBlock, blockContent});
            }

            logFile << "Preamble len: " << preamble.length() << ", version blocks: " << versionBlocks.size() << std::endl;

            // Show preamble (always, 26px font, no bullets)
            if (!preamble.empty()) {
                std::string richPreamble = buildRichText(preamble, false);
                if (!richPreamble.empty()) {
                    auto* preambleLabel = new RichTextLabel(richPreamble, 26.0f);
                    this->changelogList->addView(preambleLabel);
                }
            }

            // Show versions: if current == target, show target; otherwise show (current, target]
            int startVer = (currentVer >= targetVer) ? targetVer : (currentVer + 1);
            logFile << "Showing versions from " << startVer << " to " << targetVer << std::endl;

            bool foundAny = false;
            for (const auto& block : versionBlocks) {
                int ver = block.first;
                if (ver >= startVer && ver <= targetVer) {
                    foundAny = true;
                    std::string richContent = buildRichText(block.second, true);
                    if (!richContent.empty()) {
                        // Add version marker with 4 non-breaking spaces + bullet
                        std::string versionLine = "**" + std::to_string(ver) + "**\n";
                        std::string combined = versionLine + richContent;
                        auto* versionLabel = new RichTextLabel(combined, 22.0f);
                        this->changelogList->addView(versionLabel);
                    }
                }
            }

            if (!foundAny) {
                auto* noChangeLabel = new brls::Label(brls::LabelStyle::DESCRIPTION, "No changelog entries found.", true);
                this->changelogList->addView(noChangeLabel);
            }
        }
    }

    logFile << "=== End Debug ===" << std::endl << std::endl;
    logFile.close();

    // Create button
    this->button = (new brls::Button(brls::ButtonStyle::PRIMARY))
        ->setLabel("menus/changelog/proceed_to_update"_i18n);
    this->button->setState(brls::ButtonState::DISABLED);
    this->button->setParent(this);
    this->button->getClickEvent()->subscribe([frame, this](View* view) {
        if (!this->buttonEnabled) return; // still locked
        if (!frame->isLastStage())
            frame->nextStage();
    });

    // D-pad UP → scroll changelog list up by 80 pixels
    this->registerAction("", brls::Key::DUP, [this] {
        this->changelogList->scrollBy(-80);
        return true; // consume key, don't move focus
    }, true);

    // D-pad DOWN → scroll changelog list down by 80 pixels
    this->registerAction("", brls::Key::DDOWN, [this] {
        this->changelogList->scrollBy(80);
        return true;
    }, true);
}

ChangelogPage_Kefir::~ChangelogPage_Kefir()
{
    delete this->warningLabel;
    delete this->changelogList;  // List (ScrollView) deletes its own children
    delete this->button;
}

void ChangelogPage_Kefir::willAppear(bool resetState)
{
    this->changelogList->willAppear(resetState);
}

void ChangelogPage_Kefir::willDisappear(bool resetState)
{
    this->changelogList->willDisappear(resetState);
}

void ChangelogPage_Kefir::draw(NVGcontext* vg, int x, int y, unsigned width, unsigned height, brls::Style* style, brls::FrameContext* ctx)
{
    // Check every frame whether the list has been scrolled to the bottom
    if (!this->buttonEnabled && this->changelogList->isAtBottom()) {
        this->buttonEnabled = true;
        this->button->setState(brls::ButtonState::ENABLED);
    }

    this->warningLabel->frame(ctx);
    this->changelogList->frame(ctx);
    this->button->frame(ctx);
}

brls::View* ChangelogPage_Kefir::getDefaultFocus()
{
    return this->button;
}

void ChangelogPage_Kefir::layout(NVGcontext* vg, brls::Style* style, brls::FontStash* stash)
{
    // Warning label at top
    this->warningLabel->setWidth(this->width * 0.9f);
    this->warningLabel->invalidate(true);
    this->warningLabel->setBoundaries(
        this->x + this->width * 0.05f,
        this->y + 20,
        this->warningLabel->getWidth(),
        this->warningLabel->getHeight()
    );

    // Button at the bottom
    unsigned btnW = style->CrashFrame.buttonWidth;
    unsigned btnH = style->CrashFrame.buttonHeight;
    this->button->setBoundaries(
        this->x + this->width / 2 - btnW / 2,
        this->y + this->height - btnH - 20,
        btnW,
        btnH
    );
    this->button->invalidate();

    // Changelog list fills the space between label and button
    int listTop = this->y + 20 + (int)this->warningLabel->getHeight() + 10;
    int listBot = (int)(this->y + this->height - btnH - 20) - 10;
    int listHeight = listBot - listTop;
    if (listHeight < 0) listHeight = 0;

    this->changelogList->setBoundaries(
        this->x + 20,
        listTop,
        this->width - 40,
        (unsigned)listHeight
    );
    this->changelogList->invalidate(true);
}

int ChangelogPage_Kefir::parseKefirVersion(const std::string& version)
{
    // The version file contains e.g. "814" or "814;\n\ue016 Atmosphere: 1.7.0"
    // We want only the leading integer (stop at first non-digit after we've seen digits).
    std::string numOnly;
    for (char c : version) {
        if (std::isdigit(c)) {
            numOnly += c;
        } else if (!numOnly.empty()) {
            break;
        }
    }
    if (numOnly.empty()) return 0;
    try { return std::stoi(numOnly); }
    catch (...) { return 0; }
}

// Backward compat alias
int ChangelogPage_Kefir::parseVersion(const std::string& version)
{
    return parseKefirVersion(version);
}
