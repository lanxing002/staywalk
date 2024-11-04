#include "Engine.h"

namespace staywalk {
	shared_ptr<Engine> Engine::get_engine()
	{
		shared_ptr<Engine> engine;
		if (engine == nullptr) {
			engine = std::make_shared<Engine>();
		}
		return engine;
	}
}

