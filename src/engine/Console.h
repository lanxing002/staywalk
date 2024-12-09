#pragma once
#include "Common.h"
#include "Logger.h"
#include "rhi.h"
#include "imgui.h"
#include <string>

// Demonstrate creating a simple console window, with scrolling, filtering, completion and history.
// For the console example, we are using a more C++ like approach of declaring a class to hold both data and functions.

namespace staywalk {
    class Console
    {
    public:
        Console();
        ~Console();

        void clear_log();

        void add_log(const std::string& log, LogLevel level = LogLevel::Info);

        void draw(const std::string& log, bool* b_open);

        void exec_cmd(const std::string& log);

        int edit_callback(ImGuiInputTextCallbackData* data);

        static vector<std::pair<string, LogLevel>> log_cache_;

    private:
        char                                    input_buf_[2048];
        ImFont*                                 font_;
        vector<std::pair<LogLevel, string>>     items_;
        vector<string>                          commands_;
        vector<string>                          history_;
        int                                     history_pos_;    // -1: new line, 0..History.Size-1 browsing history.
        ImGuiTextFilter                         filter_;
        bool                                    auto_scroll_;
        bool                                    scroll_to_buttom_;
    };
}