#include "EditorUI.h"
#include "World.h"
#include "Engine.h"
#include "Actor.h"
#include "Event.h"
#include "EditorCommon.h"
#include "PyEnv.h"
#include "Renderer.h"
#include "RProgram.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <string>
#include <algorithm>

using namespace staywalk;

EditorUI::EditorUI(){
    edit_code_hanlder_ = Event::Editor_EditCode.append([this](SWCodeRef code) {
        auto text_editor = std::make_shared<TextEditor>();
        text_editor->SetCode(code);
        text_editors_.emplace_back(true, text_editor);
    });
}

EditorUI::~EditorUI()
{
    Event::Editor_EditCode.remove(edit_code_hanlder_);
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

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    setup_style();
    assets_browser_ = std::make_shared<AssetsBrowser>();

    auto codefont = io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/consola.ttf", 20.0f);
    EditorCommon::font_table_["consola"] = codefont;
}

void EditorUI::render(){
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    show_main_menu();

    for(int i = 0; i < text_editors_.size(); i++){
        std::string title = "shader##" + std::to_string(i);
        auto& [open, e] = text_editors_[i];
        e->Render(title.c_str(), &open);
    }

    //if(text_editors_.size() > 0)
    //    text_editors_.erase(std::remove_if(text_editors_.begin(), text_editors_.end(),
    //        [](const auto& e) {return !e.first; }));

    build_dock_space();
    show_world();
    show_misc();
    show_detail();
    show_console();
    show_content();

    //if (editing) ImGui::EndDisabled();
    ImGui::Render();
}

void EditorUI::render_post(){
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    
    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
    //ImGui::UpdatePlatformWindows();
}

void EditorUI::show_hide_cursor(bool show_flag){
    ImGuiIO& io = ImGui::GetIO();
    if (!show_flag) io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
    else io.ConfigFlags &= ~ImGuiConfigFlags_NoMouseCursorChange;

    io.WantCaptureKeyboard = show_flag;
    io.WantCaptureMouse = show_flag;
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
    style.IndentSpacing = 12;
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
            ImGui::DockBuilderSplitNode(center, ImGuiDir_Down, 0.65f, &bottom, &topTemp);
            ImGui::DockBuilderSplitNode(topTemp, ImGuiDir_Left, 0.18f, &left, &rightTemp);
            ImGui::DockBuilderSplitNode(rightTemp, ImGuiDir_Right, 0.30f, &right, nullptr);
        }
        ImGui::DockBuilderDockWindow("world", left);
        ImGui::DockBuilderDockWindow("misc", left);
        ImGui::DockBuilderDockWindow("detail", right);
        ImGui::DockBuilderDockWindow("content", bottom);
        ImGui::DockBuilderDockWindow("console", bottom);

        ImGui::DockBuilderFinish(mainDock);
    }

    ImGuiWindowFlags host_window_flags = 0;
    host_window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDocking;
    host_window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground;

    ImGui::Begin("host-window", nullptr, host_window_flags);
    ImGui::PopStyleVar(1);
    ImGui::DockSpace(mainDock, ImVec2(0, 0), ImGuiDockNodeFlags_NoDockingOverCentralNode | ImGuiDockNodeFlags_PassthruCentralNode);
    ImGui::End();
}

void EditorUI::show_main_menu(){
    if (ImGui::BeginMainMenuBar()){

        if (ImGui::BeginMenu("world")){
            if (ImGui::BeginMenu("load")) {
                auto path = Utility::get_worlds_dir();
                for (auto it : fs::directory_iterator(path)) {
                    if (it.path().has_filename()) {
                        auto name = it.path().filename().u8string();
                        if(ImGui::MenuItem(name.c_str())) {
                            auto world = World::load(it.path().filename().stem().u8string());
                            Engine::get_engine()->set_world(world);
                        }
                    }
                }

                ImGui::EndMenu();
            }
            if (ImGui::MenuItem("save")) { Engine::get_world()->dump(); }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void EditorUI::show_world(){
     if (!ImGui::Begin("world", &world_open_)){
         ImGui::End();
         return;
     }

     auto world = Engine::get_world();
     if (world) {
		 auto selected = Engine::get_engine()->get_selected();

		 if (ImGui::TreeNode("actor")) {
			 for (auto a : world->get_actors()) {
				 if (ImGui::Selectable(a->name_.c_str(), selected == a)) {
					 Engine::get_engine()->select(a);
				 }
			 }
			 ImGui::TreePop();
		 }

		 if (ImGui::TreeNode("camera")) {
			 for (auto a : world->get_cameras()) {
                 auto acticated_cam = world->get_activated_camera();
                 bool activated = (a.get() == acticated_cam.get());
                 ImGui::PushID((int)a->get_guid());
                 if (activated) ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.12f, 0.8f, 0.1f, 1.0f));
				 if (ImGui::Selectable(a->name_.c_str(), selected == a)) {
					 Engine::get_engine()->select(a);
				 }
                 if(activated) ImGui::PopStyleColor();

				 if (ImGui::BeginPopupContextItem("##activate-camera")) {
					 if (ImGui::Selectable("activate")) {
						 world->activate_camera(a->get_guid());
					 }
					 ImGui::EndPopup();
				 }
                 ImGui::PopID();
			 }
			 ImGui::TreePop();
		 }

		 if (ImGui::TreeNode("light")) {
			 for (auto a : world->get_lights()) {
				 if (ImGui::Selectable(a->name_.c_str(), selected == a)) {
					 Engine::get_engine()->select(a);
				 }
			 }
			 ImGui::TreePop();
		 }
     }

     ImGui::End();
}

void EditorUI::show_misc()
{
    if (!misc_open_) return;

    if (!ImGui::Begin("misc", &misc_open_)) {
        ImGui::End();
        return;
    }

    if (ImGui::TreeNode("world")) {
        static char buffer[128] = "";
        auto world = Engine::get_world();
        auto& world_name = world->get_name();

        if (ImGui::Button("rename-world")) {
            ImGui::OpenPopup("rename-world");
            if (world)
                memcpy(buffer, world_name.c_str(), world_name.size());
        }

        //if (ImGui::Button("editor-test")) {
        //    if (text_editor_) text_editor_->startEdit();
        //}
        
        if (ImGui::BeginPopupModal("rename-world", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::Text("world name:");
            ImGui::InputText("##Input", buffer, IM_ARRAYSIZE(buffer));

            if (ImGui::Button("   OK   ")) {
                auto len = strlen(buffer);
                string new_name(buffer, len);
                world->set_name(new_name);
                ImGui::CloseCurrentPopup();
            }
            ImGui::SameLine();
            if (ImGui::Button(" Cancel ")) ImGui::CloseCurrentPopup(); 
            
            ImGui::EndPopup();
        }
        ImGui::TreePop();
    }

    if (ImGui::TreeNode("Py")) {
        auto dir = Utility::get_script_dir();
        for (auto it : fs::directory_iterator(dir)) {
            if (it.path().has_filename() && it.path().has_extension()) {
                if (it.path().extension().u8string() != ".py") continue;
                auto name = it.path().stem().u8string();
                if (ImGui::Button(name.c_str())) {
                    Py::run_file(it.path());
                }
            }
        }
        ImGui::TreePop();
    }

    if (ImGui::TreeNode("shader")) {

        for (auto i = 0; i < static_cast<int>(staywalk::ProgramType::_Count); i++) {
            auto pt = static_cast<staywalk::ProgramType>(i);
            auto p = Engine::get_engine()->query_program(pt);
            ImGui::PushID((ImGuiID)p->get_guid());
            p->construct_ui(true);
            ImGui::PopID();
        }

		ImGui::TreePop();
    }

    ImGui::End();
}

void EditorUI::show_detail(){
    if (!ImGui::Begin("detail", &details_open_))
    {
        ImGui::End();
        return;
    }
    auto selected = Engine::get_engine()->get_selected();
    if (selected) selected->construct_ui(true);


    ImGui::End();
}

void EditorUI::show_console(){
    if (!console_open_) return;
    Engine::get_console()->draw("console", &console_open_);
}

void EditorUI::show_content(){
    assets_browser_->draw("content" ,&content_open_);
}

