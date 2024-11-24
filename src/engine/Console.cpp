#include "Console.h"
#include "PyEnv.h"
#include "Logger.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <string>


// Demonstrate creating a simple console window, with scrolling, filtering, completion and history.
// For the console example, we are using a more C++ like approach of declaring a class to hold both data and functions.

namespace staywalk {
    Console::Console() {
        clear_log();
        memset(InputBuf, 0, sizeof(InputBuf));
        HistoryPos = -1;

        // "CLASSIFY" is here to provide the test case where "C"+[tab] completes to "CL" and display multiple matches.
        Commands.push_back("HELP");
        Commands.push_back("HISTORY");
        Commands.push_back("CLEAR");
        Commands.push_back("CLASSIFY");
        AutoScroll = true;
        ScrollToBottom = false;

        ImGuiIO& io = ImGui::GetIO();
        font_ = io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/consola.ttf", 18.0f);
    }

    Console::~Console() {
        clear_log();
    }

    void Console::clear_log() {
        Items.clear();
    }

    void Console::add_log(const std::string& str, LogLevel level) {
        Items.emplace_back(level, str);
    }

    void Console::draw(const std::string& str, bool* b_open)
    {
        if (!ImGui::Begin(str.c_str(), b_open, ImGuiWindowFlags_NoNavInputs)){
            ImGui::End();
            return;
        }
        if (ImGui::IsWindowHovered()) {
            if (ImGui::IsKeyPressed(ImGuiKey_UpArrow)) {
                HistoryPos += 1; HistoryPos = std::min((int)(History.size()) - 1, HistoryPos);
            }
            else if (ImGui::IsKeyPressed(ImGuiKey_DownArrow)) {
                HistoryPos -= 1; HistoryPos = std::max(-1, HistoryPos);
            }
        }

        ImGui::PushFont(font_);
        // Options menu
        if (ImGui::BeginPopup("Options")) {
            ImGui::Checkbox("Auto-scroll", &AutoScroll);
            ImGui::EndPopup();
        }

        // Options, Filter
        //ImGui::SetNextItemShortcut(ImGuiMod_Ctrl | ImGuiKey_O, ImGuiInputFlags_Tooltip);
        //if (ImGui::Button("Options"))
        //    ImGui::OpenPopup("Options");
        //ImGui::SameLine();
        Filter.Draw("Filter", 180);
        ImGui::Separator();

        // Reserve enough left-over height for 1 separator + 1 input text
        const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
        if (ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), ImGuiChildFlags_NavFlattened, ImGuiWindowFlags_HorizontalScrollbar))
        {
            if (ImGui::BeginPopupContextWindow()){
                if (ImGui::Selectable("Clear")) clear_log();
                ImGui::EndPopup();
            }

            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing
            for (const auto& [level, item] : Items)
            {
                if (!Filter.PassFilter(item.c_str()))
                    continue;

                ImVec4 color;
                bool has_color = false;
                if (level == LogLevel::Error) { color = ImVec4(1.0f, 0.4f, 0.4f, 1.0f); has_color = true; }
                if (level == LogLevel::Warn) { color = ImVec4(1.0f, 0.8f, 0.6f, 1.0f); has_color = true; }
                if (has_color)
                    ImGui::PushStyleColor(ImGuiCol_Text, color);
                ImGui::TextUnformatted(item.c_str());
                if (has_color)
                    ImGui::PopStyleColor();
            }


            // Keep up at the bottom of the scroll region if we were already at the bottom at the beginning of the frame.
            // Using a scrollbar or mouse-wheel will take away from the bottom edge.
            if (ScrollToBottom || (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()))
                ImGui::SetScrollHereY(1.0f);
            ScrollToBottom = false;

            ImGui::PopStyleVar();
        }
        ImGui::EndChild();
        ImGui::Separator();

        // Command-line
        bool reclaim_focus = false;
        ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue /*| ImGuiInputTextFlags_EscapeClearsAll*//* | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory*/;
        ImGui::Text(" py ");
        ImGui::SameLine();
        if (HistoryPos != -1) {
            auto pos = int(History.size()) - 1 - HistoryPos;
            strcpy(InputBuf, History[pos].c_str());
        }
        if (ImGui::InputText("##Input", InputBuf, IM_ARRAYSIZE(InputBuf), input_text_flags)){
            char* s = InputBuf;
            if (s[0]) exec_cmd(s);
            strcpy(s, "");
            ImGui::SetKeyboardFocusHere();
            reclaim_focus = true;
        }
        // Auto-focus on window apparition
        //ImGui::SetItemDefaultFocus();
        //if (reclaim_focus)
        //     // Auto focus previous widget
        ImGui::PopFont();
        ImGui::End();
    }

    void Console::exec_cmd(const std::string& cmd){
        //add_log("# " + cmd);
        staywalk::log(cmd);
        Py::run(cmd);
        History.push_back(cmd);
        HistoryPos = -1;
    }
}