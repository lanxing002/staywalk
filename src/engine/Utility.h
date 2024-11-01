#pragma once
#include "Common.h"
#include "RenderObject.h"

namespace staywalk{
	class Utility{
	public:
		static int64_t GetRandomId();

		static void load_model(const string & path);
	};
}


