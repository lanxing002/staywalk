#pragma once
#include "Common.h"
#include <fmt/format.h>

namespace staywalk{
	class Console;
	enum class LogLevel {
		Debug, 
		Info,
		Warn,
		Error
	};

	void log_register_console(Ref<Console> console);

	void log(const string& text, LogLevel level = LogLevel::Info, bool new_line = true);

	void log(const char* str, LogLevel level = LogLevel::Info, bool new_line = true);
}

