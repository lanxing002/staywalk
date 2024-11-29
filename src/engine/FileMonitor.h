#pragma once
#include "Common.h"

#include <filesystem>
#include <functional>
#include <thread>
#include <mutex>

namespace staywalk {
	class Engine;
	struct FileMonitor {
		using CallbackType = std::function<void(const string&)>;
		using Key = pair<idtype, fs::path>;

		void start();

		void watch_file(idtype id, fs::path file_name, CallbackType callback);

		void unwatch_file(idtype id, fs::path file_name);

		// effect object in engine
		void effect();

	private:
		FileMonitor() {}
		~FileMonitor();

		Key make_key(idtype id, fs::path p) { return { id, fs::absolute(p) }; }

		map<Key, CallbackType> cb_table_;
		map<Key, fs::file_time_type> modify_table_;
		map<Key, std::string> new_content_;
		std::thread thread_;
		std::mutex mutex_;
		bool stop_ = false;

		friend class Engine;
	};
}

