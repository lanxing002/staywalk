#pragma once
#include "rhi.h"
#include "Console.h"
#include <functional>

class PopTextInput
{
public:
    PopTextInput(const std::string& label, const std::string& str);
    ~PopTextInput();

    void draw();
    bool finished() const;

    const std::string& get_text() const { return text_; }
    
    std::function<void(const std::string& str)> ok_callback;

private:
    bool done_ = false;
    std::string text_;
    const std::string popId_;
    const std::string label_;

    static long long PopId;
};