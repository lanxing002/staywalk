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
    vector<std::pair<string, LogLevel>> Console::log_cache_;

    Console::Console() {
        clear_log();
        memset(input_buf_, 0, sizeof(input_buf_));
        history_pos_ = -1;

        // "CLASSIFY" is here to provide the test case where "C"+[tab] completes to "CL" and display multiple matches.
        commands_.push_back("HELP");
        commands_.push_back("HISTORY");
        commands_.push_back("CLEAR");
        commands_.push_back("CLASSIFY");
        auto_scroll_ = true;
        scroll_to_buttom_ = false;

        ImGuiIO& io = ImGui::GetIO();
        font_ = io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/consola.ttf", 18.0f);
        for (auto& [s, l] : log_cache_) add_log(s, l);
        log_cache_.clear();
    }

    Console::~Console() {
        clear_log();
    }

    void Console::clear_log() {
        items_.clear();
    }

    void Console::add_log(const std::string& str, LogLevel level) {
        items_.emplace_back(level, str);
    }

    static int text_edit_callback_Stub(ImGuiInputTextCallbackData* data) {
        Console* console = (Console*)data->UserData;
        return console->edit_callback(data);
    }

    void Console::draw(const std::string& str, bool* b_open)
    {
        if (!ImGui::Begin(str.c_str(), b_open, ImGuiWindowFlags_NoNavInputs)){
            ImGui::End();
            return;
        }

        ImGui::PushFont(font_);
        
        // Options menu
        if (ImGui::BeginPopup("Options")){
            ImGui::Checkbox("Auto-scroll", &auto_scroll_);
            ImGui::EndPopup();
        }

        // Main window
        if (ImGui::Button("Options"))
            ImGui::OpenPopup("Options");
        ImGui::SameLine();
        filter_.Draw("Filter", 180);
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
            for (const auto& [level, item] : items_)
            {
                if (!filter_.PassFilter(item.c_str()))
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
            if (scroll_to_buttom_ || (auto_scroll_ && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()))
                ImGui::SetScrollHereY(1.0f);
            scroll_to_buttom_ = false;
            ImGui::PopStyleVar();
        }
        ImGui::EndChild();
        ImGui::Separator();
        bool reclaim_focus = false;
        ImGuiInputTextFlags input_text_flags =  ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackHistory | ImGuiInputTextFlags_CallbackResize;
        ImGui::Text(" py ");
        ImGui::SameLine();
        
        //if (HistoryPos != -1) {
        //    auto pos = int(History.size()) - 1 - HistoryPos;
        //    strcpy(InputBuf, History[pos].c_str());
        //}

        if (ImGui::InputText("##Input", input_buf_, IM_ARRAYSIZE(input_buf_), input_text_flags, &text_edit_callback_Stub, (void*)this)){
            char* s = input_buf_;
            if (s[0]) exec_cmd(s);
            strcpy(s, "");
            reclaim_focus = true;
        }
        if (reclaim_focus)
            ImGui::SetKeyboardFocusHere(-1);
        ImGui::PopFont();
        ImGui::End();
    }

    void Console::exec_cmd(const std::string& cmd){
        staywalk::log(cmd);
        Py::run(cmd);
        history_.push_back(cmd);
        history_pos_ = -1;
    }

    int Console::edit_callback(ImGuiInputTextCallbackData* data){
        //AddLog("cursor: %d, selection: %d-%d", data->CursorPos, data->SelectionStart, data->SelectionEnd);
        switch (data->EventFlag)
        {
        case ImGuiInputTextFlags_CallbackHistory: {
            const int prev_history_pos = history_pos_;
            if (data->EventKey == ImGuiKey_UpArrow){
                if (history_pos_ == -1)
                    history_pos_ = int(history_.size()) - 1;
                else if (history_pos_ > 0)
                    history_pos_--;
            }
            else if (data->EventKey == ImGuiKey_DownArrow){
                if (history_pos_ != -1)
                    if (++history_pos_ >= history_.size())
                        history_pos_ = -1;
            }

            if (prev_history_pos != history_pos_){
                const char* history_str = (history_pos_ >= 0) ? history_[history_pos_].c_str() : "";
                data->DeleteChars(0, data->BufTextLen);
                data->InsertChars(0, history_str);
            }
        }
        }
        return 0;
    }
}