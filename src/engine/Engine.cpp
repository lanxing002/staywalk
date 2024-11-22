#include "Engine.h"

namespace staywalk {
	shared_ptr<Engine> Engine::get_engine(){
		static shared_ptr<Engine> engine{nullptr};
		if (engine == nullptr) {
			engine = shared_ptr<Engine>(new Engine);
			engine->console_ = get_console();
		}
		return engine;
	}

	Ref<Console> Engine::get_console()
	{
		static Ref<Console> console{nullptr};
		if (console == nullptr) {
			console = shared_ptr<Console>(new Console);
		}
		return console;
	}

	void Engine::load_world(const string& name){
		world_ = World::load(name);
	}
	
	Engine::Engine(){
		////world_ = World::create_empty_world("default");
		//world_ = World::load_marry_world();
		world_ = World::load("marry-world");
		console_ = std::make_shared<Console>();
	}
	
	Engine::~Engine(){
	}
}

