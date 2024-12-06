#pragma once

#include "Common.h"
#include "Utility.h"
#include "Console.h"
#include "RenderInfo.h"
#include "FileMonitor.h"
#include "Renderer.h"
#include "InputManager.h"

//#include <memory>
//#include <unordered_map>

namespace staywalk{
	class Object;
	class Actor;

	class sw_Class(nogui; nojson) Engine{
	public:
		// engine functions
		sw_Func() static shared_ptr<Engine> get_engine();
		sw_Func() static shared_ptr<World> get_world() { return Engine::get_engine()->world_; }
		sw_Func() static Ref<Console> get_console() { return Engine::get_engine()->console_; }

		sw_Func() void monitor_file(FileMonitor::Key key, const FileMonitor::CallbackType& cb);
		sw_Func() void cancel_monitor_file(FileMonitor::Key key);

		void shutdown();
		~Engine();
		//end of engine functions

		sw_Func() void set_world(WorldRef world);
		sw_Func() RProgramRef query_program(ProgramType pt);
		sw_Func() InputManager& get_input_mgr() { return input_mgr_; }
		InputManager* get_input_mgr_raw() { return &input_mgr_; }
		sw_Func() vec2 get_view_size() { return view_size_; }
		sw_Func() void set_view_size(vec2 value) { view_size_ = value; }

		void initialize();
		void render_update();
		void logic_update(float delta);
		void event_clear() { input_mgr_.clear(); }

	public:
		sw_Func() void select(Ref<GameObject> target) { selelcted_ = target; }
		sw_Func() Ref<GameObject> get_selected() { return selelcted_; }

	private:
		/**
		* @load necessary data
		*/
		Engine();

	private:
		FileMonitor file_monitor_;
		Ref<Console> console_{nullptr};
		Renderer renderer_;

		GameObjectRef selelcted_{ nullptr };
		WorldRef world_{ nullptr };

		vec2 view_size_;
		InputManager input_mgr_;
	};
}



