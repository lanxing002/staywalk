#pragma once
#include "Common.h"
#include "Utility.h"
#include "World.h"
#include "Console.h"

#include <memory>
#include <unordered_map>


namespace staywalk{
	class Object;
	class Actor;

	class Engine{
	public:
		// engine functions
		static shared_ptr<Engine> get_engine();
		static shared_ptr<World> get_world() { return Engine::get_engine()->world_; }
		static Ref<Console> get_console() { return Engine::get_engine()->console_; }

		~Engine();
		//end of engine functions

		void load_world(const string& name);

	public:
		//editor function
		void select(shared_ptr<Actor> target) { selelcted_ = target; }
		shared_ptr<Actor> get_selected() { return selelcted_; }

		// end of editor function

	private:
		Engine();

	private:
		shared_ptr<World> world_;
		friend class std::shared_ptr<Engine>;

		// memeber for editor
		shared_ptr<Actor> selelcted_;

		shared_ptr<Console> console_;

		// end member for editor
	};
}



