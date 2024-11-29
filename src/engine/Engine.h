#pragma once

#include "Common.h"
#include "Utility.h"
#include "World.h"
#include "Console.h"
#include "Light.h"
#include "Camera.h"

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

		~Engine();
		//end of engine functions

		sw_Func() void set_world(WorldRef world);

		void init_editor_data();

		void render_update(RenderInfo& info);

		void logic_update(float delta);


	public:
		//editor function
		sw_Func() void select(Ref<GameObject> target) { selelcted_ = target; }
		sw_Func() Ref<GameObject> get_selected() { return selelcted_; }

		// end of editor function

	private:
		/**
		* @load necessary data
		*/
		Engine();

	private:
		WorldRef world_{ nullptr };

		Ref<GameObject> selelcted_{nullptr};
		Ref<Console> console_{nullptr};
	};
}



