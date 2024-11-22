#include "Logger.h"
#include <fmt/color.h>

void staywalk::log(LogLevel level, string& text, bool new_line){
	log(level, text.c_str(), new_line);
}

void staywalk::log(LogLevel level, const char* str, bool new_line){
	auto color = fmt::color::white;
	switch (level)
	{
	case staywalk::Warining:
		color = fmt::color::yellow;
		break;
	case staywalk::Error:
		color = fmt::color::red;
		break;
	default:
		break;
	}
	if (level == LogLevel::Error || level == LogLevel::Warining)
		fmt::print(fmt::fg(color), str);
	else
		fmt::print(str);

	if (new_line) fmt::println("");
	return;
}
