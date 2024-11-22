#pragma once
#include "Common.h"
#include <fmt/format.h>

namespace staywalk{
	enum LogLevel {
		Debug, 
		Info,
		Warining,
		Error
	};

	void log(LogLevel level, string& text, bool new_line = true);

	void log(LogLevel level, const char* str, bool new_line = true);

}

