#include "rhi.h"
#include "FileMonitor.h"
#include "Logger.h"

#include <chrono>

using namespace staywalk;

void FileMonitor::start(){
	thread_ = std::thread([this]() {
		while (!stop_){
			{
				auto lock = std::lock_guard<std::mutex>(mutex_);
				for(auto& [k, last_time] : modify_table_){
					if (fs::exists(k.second)) continue;
					auto new_time = fs::last_write_time(k.second);
					if (new_time == last_time) continue;

					ifstream ifs = ifstream(k.second, std::ios::in);
					if(!ifs) continue;
					std::string content((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
					new_content_[k] = content;
					last_time = new_time;
				}
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(30));
		}
	});
}

void FileMonitor::watch_file(idtype id, fs::path file_name, CallbackType callback){

	fs::file_time_type modify_time;
	if (fs::exists(file_name)) {
		modify_time = fs::last_write_time(file_name);
	}
	auto key = make_key(id, file_name);
	cb_table_[key] = callback;
	{
		auto lock = std::lock_guard<std::mutex>(mutex_);
		modify_table_[key] = modify_time;
	}
}

void FileMonitor::effect(){
	auto lock = std::lock_guard<std::mutex>(mutex_);
	for (auto& [k, c] : new_content_) {
		auto it = cb_table_.find(k);
		if (it == cb_table_.end()) continue;
		it->second(c);
	}
	new_content_.clear();
}

void staywalk::FileMonitor::unwatch_file(idtype id, fs::path file_name){
	auto k = make_key(id, file_name);
	auto it = cb_table_.find(k);
	if (it != cb_table_.end()){
		log(fmt::format("unwatch_file failed: {}, {} have not been watched", id, file_name.u8string()),
			LogLevel::Warn);
		return;
	}

	cb_table_.erase(it);
	modify_table_.erase(k);
}

staywalk::FileMonitor::~FileMonitor(){
	stop_ = true;
	thread_.join();
}
