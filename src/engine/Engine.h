#pragma once
#include "Common.h"
#include "Utility.h"
#include <memory>
#include <unordered_map>

namespace staywalk{
	class Object;
	class Actor;
	class Engine{


	public:
		static shared_ptr<Engine> get_engine();
	};
}



