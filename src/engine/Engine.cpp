#include "Engine.h"
#include "Logger.h"
#include "PyEnv.h"
#include "rhi.h"
#include "Event.h"

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
		//world_ = World::load_marry_world();
		//world_ = World::load("marry-world");
		world_ = nullptr;
		console_ = nullptr;
		Py::run("");
	}
	
	Engine::~Engine(){
	}

	void Engine::set_world(WorldRef	world){
		// setup light
		world_ = world;
		selelcted_ = nullptr;
		Event::World_AssetChanged();
	}

	void Engine::init_editor_data() {
		console_ = std::make_shared<Console>();
		log_register_console(console_);
	}

	void Engine::render_update(RenderInfo& info){

	}

	void Engine::logic_update(float delta){
		if (world_) world_->logic_update();
	}

}

