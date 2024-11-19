#include "EditorUI.h"
#include "World.h"
#include "Engine.h"
#include "Actor.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <string>

using namespace staywalk;
EditorUI::EditorUI(){
}

EditorUI::~EditorUI()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void EditorUI::initialize(GLFWwindow* window){
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    const char* glsl_version = "#version 130";
    ImGui_ImplOpenGL3_Init(glsl_version);

    setup_style();
}

void EditorUI::render(){
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    //style.Colors[ImGuiCol_FrameBg] = ImVec4(182, 182, 182, 255);
    //showEditorMenu();
    show_main_menu();
    build_dock_space();
    show_actors();
    //showEditorWorldObjectsWindow(&m_worldObjectsOpen);
    show_details();
    show_console();
    //showFileContentWindow(&m_fileContentOpen);
    //showConsoleWindow(&m_consoleOpen);

    ImGui::Render();
}

void EditorUI::render_post(){
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    ImGui::UpdatePlatformWindows();
}

void EditorUI::setup_style(){
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
    io.IniFilename = NULL;										// style not to file

    io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 20.0f);

    // config color style 
    auto& style = ImGui::GetStyle();
    ImGui::StyleColorsClassic();
    style.Colors[ImGuiCol_WindowBg] = ImVec4(49 / 255.0f, 46 / 255.0f, 46 / 255.0f, 217 / 255.0f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(80 / 255.0f, 80/ 255.0f, 80 / 255.0f, 217 / 255.0f);

    // ui style
    style.WindowPadding = ImVec2(3.0, 3.0);
    style.FramePadding = ImVec2(3.0, 3.0);
    style.ItemSpacing = ImVec2(3.0, 4.0);
    style.ItemInnerSpacing = ImVec2(3.0, 4.0);
    style.WindowTitleAlign = ImVec2(0.5, 0.5);
    style.WindowBorderSize = 0.0;
    style.FrameBorderSize = 0.0;
    style.TabBarBorderSize = 0.0;

    style.WindowRounding = 10.0;
    style.TabRounding = 10.0;
    style.FrameRounding = 8.0;
    style.GrabRounding = 8.0;
    style.TabRounding = 8.0;

    style.ButtonTextAlign = ImVec2(0.5, 0.5);
    style.SelectableTextAlign = ImVec2(0.0, 0.5);
}

void EditorUI::build_dock_space(){
    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(main_viewport->WorkPos);
    ImGui::SetNextWindowSize(main_viewport->WorkSize);
    ImGui::SetNextWindowViewport(main_viewport->ID);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGuiID mainDock = ImGui::GetID("main-dock");
    if (ImGui::DockBuilderGetNode(mainDock) == nullptr){
        ImGui::DockBuilderAddNode(mainDock, ImGuiDockNodeFlags_DockSpace);

        ImGui::DockBuilderSetNodeSize(mainDock, ImVec2(main_viewport->WorkSize.x, main_viewport->WorkSize.y));
        ImGuiID center = mainDock;
        ImGuiID bottom;
        ImGuiID left, right;

        {
            ImGuiID rightTemp, topTemp;
            ImGui::DockBuilderSplitNode(center, ImGuiDir_Down, 0.25f, &bottom, &topTemp);
            ImGui::DockBuilderSplitNode(topTemp, ImGuiDir_Left, 0.25f, &left, &rightTemp);
            ImGui::DockBuilderSplitNode(rightTemp, ImGuiDir_Right, 0.40f, &right, nullptr);
        }
        ImGui::DockBuilderDockWindow("actors", left);
        ImGui::DockBuilderDockWindow("details", right);
        ImGui::DockBuilderDockWindow("File-Content", bottom);
        ImGui::DockBuilderDockWindow("Console", bottom);

        ImGui::DockBuilderFinish(mainDock);
    }

    ImGuiWindowFlags host_window_flags = 0;
    host_window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDocking;
    host_window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground;

    ImGui::Begin("hostost-window", nullptr, host_window_flags);
    ImGui::PopStyleVar(1);
    ImGui::DockSpace(mainDock, ImVec2(0, 0), ImGuiDockNodeFlags_NoDockingOverCentralNode | ImGuiDockNodeFlags_PassthruCentralNode);
    ImGui::End();
}

void EditorUI::show_main_menu(){
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
            if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "CTRL+X")) {}
            if (ImGui::MenuItem("Copy", "CTRL+C")) {}
            if (ImGui::MenuItem("Paste", "CTRL+V")) {}

            if (ImGui::MenuItem("save world")) {
                Engine::get_world()->dump();
            }

            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void EditorUI::show_actors(){
     if (!ImGui::Begin("actors")){
         ImGui::End();
         return;
     }

     auto world = Engine::get_world();
     auto actors = world->get_all_actors();
     auto selected = Engine::get_engine()->get_selected();
     for (auto a : actors) {
         if (ImGui::Selectable(a->name.c_str(), selected == a)) {
             Engine::get_engine()->select(a);
         }
     }

     ImGui::End();
}

void EditorUI::show_details(){
    if (!ImGui::Begin("details"))
    {
        ImGui::End();
        return;
    }
    auto selected = Engine::get_engine()->get_selected();
    if (selected) selected->construct_ui(false);


    ImGui::End();
}

void EditorUI::show_console(){
    Engine::get_console()->draw("Console");
}

void EditorUI::showFileContentWindow(bool* opened){
    if (!*opened) return;
    if (!ImGui::Begin("File-Content", opened, ImGuiWindowFlags_None))
    {
        ImGui::End();
        return;
    }

    ImGui::Text("FileContent window text");

    ImGui::End();
}

void EditorUI::showConsoleWindow(bool* opened)
{
    if (!*opened) return;
    if (!ImGui::Begin("Console", opened, ImGuiWindowFlags_None))
    {
        ImGui::End();
        return;
    }

    ImGui::Text("console window text1");
    ImGui::Text("console window text2");

    ImGui::End();
}

//
//
//// Main code
//int main(int, char**)
//{
//    glfwSetErrorCallback(glfw_error_callback);
//    if (!glfwInit())
//        return 1;
//
//    // Decide GL+GLSL versions
//#if defined(IMGUI_IMPL_OPENGL_ES2)
//    // GL ES 2.0 + GLSL 100
//    const char* glsl_version = "#version 100";
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
//    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
//#elif defined(__APPLE__)
//    // GL 3.2 + GLSL 150
//    const char* glsl_version = "#version 150";
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
//#else
//    // GL 3.0 + GLSL 130
//    const char* glsl_version = "#version 130";
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
//    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
//    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
//#endif
//
//    // Create window with graphics context
//    GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", nullptr, nullptr);
//    if (window == nullptr)
//        return 1;
//    glfwMakeContextCurrent(window);
//    glfwSwapInterval(1); // Enable vsync
//
//    // Setup Dear ImGui context
//    //IMGUI_CHECKVERSION();
//    ImGui::CreateContext();
//    ImGuiIO& io = ImGui::GetIO(); (void)io;
//    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
//    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
//    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
//    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
//    //io.ConfigViewportsNoAutoMerge = true;
//    //io.ConfigViewportsNoTaskBarIcon = true;
//
//    // Setup Dear ImGui style
//    ImGui::StyleColorsDark();
//    //ImGui::StyleColorsLight();
//
//    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
//    ImGuiStyle& style = ImGui::GetStyle();
//    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
//    {
//        style.WindowRounding = 0.0f;
//        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
//    }
//
//    // Setup Platform/Renderer backends
//    ImGui_ImplGlfw_InitForOpenGL(window, true);
//#ifdef __EMSCRIPTEN__
//    ImGui_ImplGlfw_InstallEmscriptenCallbacks(window, "#canvas");
//#endif
//    ImGui_ImplOpenGL3_Init(glsl_version);
//
//    // Load Fonts
//    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
//    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
//    // - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
//    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
//    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
//    // - Read 'docs/FONTS.md' for more instructions and details.
//    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
//    // - Our Emscripten build process allows embedding fonts to be accessible at runtime from the "fonts/" folder. See Makefile.emscripten for details.
//    //io.Fonts->AddFontDefault();
//    io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 20.0f);
//    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
//    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
//    //io.Fonts->AddFontFromFileTTF(R"(C:\Users\Lenovo\Documents\gly\git_stars\gl\staywalk\resource\miscellaneous\fonts)", 18.0f);
//    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
//    //IM_ASSERT(font != nullptr);
//
//    // Our state
//    bool show_demo_window = true;
//    bool show_another_window = false;
//    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
//    EditorUI ui;
//    ui.initialize();
//
//    // Main loop
//#ifdef __EMSCRIPTEN__
//    // For an Emscripten build we are disabling file-system access, so let's not attempt to do a fopen() of the imgui.ini file.
//    // You may manually call LoadIniSettingsFromMemory() to load settings from your own storage.
//    io.IniFilename = nullptr;
//    EMSCRIPTEN_MAINLOOP_BEGIN
//#else
//    while (!glfwWindowShouldClose(window))
//#endif
//    {
//        // Poll and handle events (inputs, window resize, etc.)
//        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
//        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
//        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
//        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
//        glfwPollEvents();
//
//        // Start the Dear ImGui frame
//        ImGui_ImplOpenGL3_NewFrame();
//        ImGui_ImplGlfw_NewFrame();
//
//        //ImGui::NewFrame();
//        ImGui::NewFrame();
//        ui.render();
//
//        ImGui::Render();
//        int display_w, display_h;
//        glfwGetFramebufferSize(window, &display_w, &display_h);
//        glViewport(0, 0, display_w, display_h);
//        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
//        glClear(GL_COLOR_BUFFER_BIT);
//        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//
//        // Update and Render additional Platform Windows
//        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
//        //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
//        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
//        {
//            GLFWwindow* backup_current_context = glfwGetCurrentContext();
//            ImGui::UpdatePlatformWindows();
//            ImGui::RenderPlatformWindowsDefault();
//            glfwMakeContextCurrent(backup_current_context);
//        }
//
//        glfwSwapBuffers(window);
//    }
//#ifdef __EMSCRIPTEN__
//    EMSCRIPTEN_MAINLOOP_END;
//#endif
//
//    // Cleanup
//    ImGui_ImplOpenGL3_Shutdown();
//    ImGui_ImplGlfw_Shutdown();
//    ImGui::DestroyContext();
//
//    glfwDestroyWindow(window);
//    glfwTerminate();
//
//    return 0;
//}
