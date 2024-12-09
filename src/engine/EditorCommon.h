#pragma once

#include <imgui.h>
#include <map>
#include <string>

class EditorCommon {
public:
    static std::map<std::string, ImFont*> font_table_;
};
