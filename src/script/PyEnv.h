#pragma once
#include "Common.h"
namespace staywalk {
	class Py{
	public:
		static void __init();
		static void run(const string& code);

		static void run_file(const fs::path& file);
	};
}

