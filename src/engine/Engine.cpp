#include "Engine.h"

namespace staywalk {
	shared_ptr<Engine> Engine::get_engine(){
		static shared_ptr<Engine> engine{nullptr};
		if (engine == nullptr) {
			engine = shared_ptr<Engine>(new Engine);
		}
		return engine;
	}
	
	Engine::Engine(){
		//world_ = World::create_empty_world("default");
		world_ = World::load_marry_world();
		console_ = std::make_shared<Console>();
	}
	
	Engine::~Engine(){
	}
}

