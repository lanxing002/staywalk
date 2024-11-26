#pragma once
#include "rhi.h"
#include "Console.h"
#include "PopInput.h"
#include "TextEditor.h"
#include "AssetBrowser.h"

#include <list>


class EditorUI
{
public:
    EditorUI();
    ~EditorUI();

    void initialize(GLFWwindow* window);
    void render();
    void render_post();

private:
    void setup_style();
    void build_dock_space();

    void show_main_menu();
    void show_world();
    void show_misc();

    void show_detail();
    void show_console();
    void show_content();

private:
    std::shared_ptr<TextEditor> text_editor_{nullptr};
    std::shared_ptr<AssetsBrowser> assets_browser_{nullptr};

    bool world_open_ = true;
    bool details_open_ = true;
    bool console_open_ = true;
    bool content_open_ = true;
    bool misc_open_ = true;
};