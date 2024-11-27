#include "Engine.h"
#include "Logger.h"
#include "PyEnv.h"

namespace staywalk {
	shared_ptr<Engine> Engine::get_engine(){
		static shared_ptr<Engine> engine{nullptr};
		if (engine == nullptr) {
			engine = shared_ptr<Engine>(new Engine);
		}
		return engine;
	}


	void Engine::load_world(const string& name){
		world_ = World::load(name);
	}
	
	Engine::Engine(){
		////world_ = World::create_empty_world("default");
		world_ = World::load_marry_world();
		//world_ = World::load("marry-world");
		console_ = nullptr;
		Py::run("");
	}
	
	Engine::~Engine(){
	}

	void Engine::init_editor_data(){
		console_ = std::make_shared<Console>();
		log_register_console(console_);
	}
}

