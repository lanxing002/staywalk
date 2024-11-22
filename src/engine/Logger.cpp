#include "Logger.h"
#include "Engine.h"
#include <fmt/color.h>
#include <fmt/chrono.h>
#include <chrono>
using namespace std::chrono;

void staywalk::log(string& text, LogLevel level, bool new_line){
	log(text.c_str(), level, new_line);
}

void staywalk::log(const char* str, LogLevel level, bool new_line){
	std::time_t now = std::time(nullptr);
	string text_with_time = fmt::format("[{:%Y-%m-%d %H:%M:%S}]:  {}", fmt::localtime(now), str);

	static auto console = Engine::get_console();
	if (!console) console = Engine::get_console();
	if (console) {
		console->add_log(text_with_time, level);
	}
	else {
		fmt::println(text_with_time);
	}
	return;
}
