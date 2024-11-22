#pragma once
#include "Common.h"
#include <fmt/format.h>

namespace staywalk{
	enum LogLevel {
		Debug, 
		Info,
		Warning,
		Error
	};

	void log(string& text, LogLevel level = LogLevel::Info, bool new_line = true);

	void log(const char* str, LogLevel level = LogLevel::Info, bool new_line = true);

}

