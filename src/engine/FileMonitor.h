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
		static Key make_key(idtype id, fs::path p) { return { id, fs::absolute(p) }; }

		void start();

		void watch_file(const Key& key, const CallbackType& callback);

		void unwatch_file(const Key& key);

		// effect object in engine
		void effect();

	private:
		FileMonitor() {}
		~FileMonitor();

		map<Key, CallbackType> cb_table_;
		map<Key, fs::file_time_type> modify_table_;
		map<Key, std::string> new_content_;
		std::thread thread_;
		std::mutex mutex_;
		bool stop_ = false;

		friend class Engine;
	};
}

