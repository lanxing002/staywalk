#include "Engine.h"
#include "Logger.h"
#include "PyEnv.h"
#include "rhi.h"
#include "Event.h"
#include "World.h"
#include "DeferredRenderer.h"

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
		renderer_ = std::make_shared<DeferredRenderer>();
		Py::run("");
		file_monitor_.start();
	}

	void Engine::shutdown()
	{
		renderer_->destroy();
		world_ = nullptr;
		console_ = nullptr;
		selelcted_ = nullptr;
		destroy_ = true;
	}


	Engine::~Engine() {
	}

	void Engine::set_world(const string world_name){
		// setup light
		world_ = nullptr;  // destroy all asset
		Event::World_AssetChanged();
		auto world = World::load(world_name);
		world_ = world;
		selelcted_ = nullptr;
		Event::World_AssetChanged();
	}

	staywalk::StdProgramRef Engine::query_program(ProgramType pt)
	{
		return renderer_->query_program(pt);
	}

	void Engine::initialize() {
		collect_gpu_info();
		console_ = std::make_shared<Console>();
		log_register_console(console_);

		renderer_->initialize();
	}

	void Engine::render_update(float delta, unsigned int frame_count){
		renderer_->render(delta, frame_count);
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

	void Engine::collect_gpu_info() {
		GLint max_work_group_size[3];
		GLint max_work_group_invocations;
		GLint max_work_group_count[3];

		for (int i = 0; i < 3; ++i) {
			glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, i, &max_work_group_size[i]);
		}

		glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &max_work_group_invocations);

		for (int i = 0; i < 3; ++i) {
			glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, i, &max_work_group_count[i]);
		}

		log(fmt::format("Max Work Group Size ({}, {}, {})", max_work_group_size[0], max_work_group_size[1], max_work_group_size[2]));
		log(fmt::format("Max Work Group Invocations ({})", max_work_group_invocations));
		log(fmt::format("Max Work Group Count ({}, {}, {})", max_work_group_count[0], max_work_group_count[1], max_work_group_count[2]));

		assert(kCSLocalSize.x * kCSLocalSize.y * kCSLocalSize.z <= max_work_group_invocations);
	}
}

