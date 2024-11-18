#pragma once
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

        void add_log(const std::string& log);

        void draw(const std::string& log);

        void exec_cmd(const std::string& log);

        // In C++11 you'd be better off using lambdas for this sort of forwarding callbacks
        //static int TextEditCallbackStub(ImGuiInputTextCallbackData* data);
        //int TextEditCallback(ImGuiInputTextCallbackData* data);

    private:
        char                  InputBuf[256];
        ImVector<std::string> Items;
        ImVector<const char*> Commands;
        ImVector<char*>       History;
        int                   HistoryPos;    // -1: new line, 0..History.Size-1 browsing history.
        ImGuiTextFilter       Filter;
        bool                  AutoScroll;
        bool                  ScrollToBottom;
    };
}