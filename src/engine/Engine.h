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
		sw_Func() static void set_world(Ref<World> world) { if (world) Engine::get_engine()->world_ = world; }
		sw_Func() static Ref<Console> get_console() { return Engine::get_engine()->console_; }

		~Engine();
		//end of engine functions

		void set_world(WorldRef	world);

		void init_editor_data();


		sw_Func() void set_camera(CameraRef camera);

		sw_Func() mat4 get_camera() { return camera_mat_; }

		RLight& get_light_mgr() { return light_mgr_; }

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
		shared_ptr<World> world_{ nullptr };

		// member for editor
		Ref<GameObject> selelcted_{nullptr};
		Ref<Console> console_{nullptr};
		// end member for editor


		RLight light_mgr_;
		mat4 camera_mat_;
	};
}



