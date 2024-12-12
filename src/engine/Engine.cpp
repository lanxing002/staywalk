#include "Engine.h"
#include "Logger.h"
#include "PyEnv.h"
#include "rhi.h"
#include "Event.h"
#include "World.h"

namespace staywalk {
	shared_ptr<Engine> Engine::get_engine(){
		static shared_ptr<Engine> engine{nullptr};
		if (engine == nullptr) {
			engine = shared_ptr<Engine>(new Engine);
		}
		assert(!engine->destroy_);
		return engine;
	}

	
	Engine::Engine(){
		//world_ = World::create_empty_world("default");
		//world_ = World::load_marry_world();
		//world_ = World::load("marry-world");
		world_ = nullptr;
		console_ = nullptr;
		Py::run("");
		file_monitor_.start();
	}

	void Engine::shutdown()
	{
		renderer_.destroy();
		world_ = nullptr;
		console_ = nullptr;
		selelcted_ = nullptr;
		destroy_ = true;
	}


	Engine::~Engine() {
	}

	void Engine::set_world(WorldRef	world){
		// setup light
		world_ = world;
		selelcted_ = nullptr;
		Event::World_AssetChanged();
	}

	staywalk::ProgramRef Engine::query_program(ProgramType pt)
	{
		return renderer_.query_program(pt);
	}

	void Engine::initialize() {
		console_ = std::make_shared<Console>();
		log_register_console(console_);

		renderer_.initialize();
	}

	void Engine::render_update(float delta, unsigned int frame_count){
		renderer_.render(delta, frame_count);
	}

	void Engine::logic_update(float delta){
		file_monitor_.effect();
		if (world_) world_->logic_update(delta);
	}


	void Engine::monitor_file(FileMonitor::Key key, const FileMonitor::CallbackType& cb){
		file_monitor_.watch_file(key, cb);
	}

	void Engine::cancel_monitor_file(FileMonitor::Key key){
		file_monitor_.unwatch_file(key);
	}

}

