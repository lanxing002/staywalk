#include "Logger.h"
#include "Engine.h"
#include <fmt/color.h>
#include <fmt/chrono.h>
#include <chrono>
using namespace std::chrono;

const char* get_level_str(const staywalk::LogLevel level) {
	switch (level) {
	case staywalk::LogLevel::Debug:		return "debug";
	case staywalk::LogLevel::Info:		return "info ";
	case staywalk::LogLevel::Warn:	return "warn ";
	default:							return "error";
	}
}

void staywalk::log(const string& text, LogLevel level, bool new_line){
	log(text.c_str(), level, new_line);
}

void staywalk::log(const char* str, LogLevel level, bool new_line){
	std::time_t now = std::time(nullptr);
	//[{:% Y - % m - % d % H : % M : % S}]
	string text_with_time = fmt::format("[{:%H:%M:%S}] [{:<5}]: {}", fmt::localtime(now), get_level_str(level), str);

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
