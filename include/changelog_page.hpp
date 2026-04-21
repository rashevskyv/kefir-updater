#pragma once

#include <borealis.hpp>

class ChangelogPage : public brls::AppletFrame
{
private:
    brls::List* list;
    brls::ListItem* listItem;

public:
    ChangelogPage();
    void ShowChangelogContent(const std::string version, const std::string content);
};

class ChangelogPage_Kefir : public brls::View
{
protected:
    brls::Button* button = nullptr;
    brls::Label* warningLabel = nullptr;
    brls::List* changelogList = nullptr;
    // Note: no outer scrollView — brls::List IS already a ScrollView

    int parseKefirVersion(const std::string& version);
    int parseVersion(const std::string& version);  // backward compat alias

public:
    ChangelogPage_Kefir(brls::StagedAppletFrame* frame, const std::string& currentVersion, const std::string& targetVersion, const std::string& url = "");
    ~ChangelogPage_Kefir();

    void draw(NVGcontext* vg, int x, int y, unsigned width, unsigned height, brls::Style* style, brls::FrameContext* ctx) override;
    void layout(NVGcontext* vg, brls::Style* style, brls::FontStash* stash) override;
    void willAppear(bool resetState = false) override;
    void willDisappear(bool resetState = false) override;
    brls::View* getDefaultFocus() override;
};