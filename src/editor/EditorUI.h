#pragma once
#include "rhi.h"
#include "Console.h"
#include "PopInput.h"
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
    std::list<PopTextInput> pop_inputs_;

    bool m_worldObjectsOpen = true;
    bool m_detailsOpen = true;
    bool m_consoleOpen = true;
    bool m_fileContentOpen = true;
};