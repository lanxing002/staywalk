#pragma once
#include "Common.h"
#include "RenderObject.h"

namespace staywalk{
	class Utility{
	public:
		static int64_t GetRandomId();

		static bool check_ifstream(const std::ifstream& fstrm);
		
		static bool check_ofstream(const std::ofstream& fstrm);

		static void load_model(const string & path);
	};
}


