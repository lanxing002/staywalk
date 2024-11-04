#include "Logger.h"
#include <fmt/color.h>

void staywalk::log(LogLevel level, string& text, bool new_line){
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
		fmt::print(fmt::fg(color), text);
	else
		fmt::print( text);

	if (new_line) fmt::println("");
	return;
}
