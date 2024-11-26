#include "Logger.h"
#include "Engine.h"
#include <fmt/color.h>
#include <fmt/chrono.h>
#include <chrono>
using namespace std::chrono;

staywalk::Ref<staywalk::Console> kConsole{ nullptr };

const char* get_level_str(const staywalk::LogLevel level) {
	switch (level) {
	case staywalk::LogLevel::Debug:		return "debug";
	case staywalk::LogLevel::Info:		return "info ";
	case staywalk::LogLevel::Warn:		return "warn ";
	default:							return "error";
	}
}


void staywalk::log_register_console(Ref<Console> console){
	kConsole = console;
}

void staywalk::log(const string& text, LogLevel level, bool new_line){
	log(text.c_str(), level, new_line);
}

void staywalk::log(const char* str, LogLevel level, bool new_line){
	std::time_t now = std::time(nullptr);
	string text_with_time = fmt::format("[{:%H:%M:%S}] [{:<5}]: ", fmt::localtime(now), get_level_str(level)) + str;
	//fmt::println(text_with_time);
	if (kConsole)
		kConsole->add_log(text_with_time, level);
	else
		Console::log_cache_.push_back({text_with_time, level});

	return;
}
