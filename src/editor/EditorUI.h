#pragma once
#include "rhi.h"

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
    void show_actors();

    void show_details();
    void showFileContentWindow(bool* opened);
    void showConsoleWindow(bool* opened);

private:
    bool m_worldObjectsOpen = true;
    bool m_detailsOpen = true;
    bool m_consoleOpen = true;
    bool m_fileContentOpen = true;
};