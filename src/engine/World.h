#pragma once
#include "Common.h"

namespace staywalk {
	class Object;
	class Actor;
	class World;

	using PObject = shared_ptr<Object>;
	using PActor = shared_ptr<Actor>;
	using PWorld = shared_ptr<World>;

	class World {
	public:
		~World();

		void dump();

		static PWorld create_empty_world(const string& world_name);
		// test, need to serizalize to scene file
		static PWorld load_marry_world();
		static shared_ptr<World> load(const string& name);

		const vector<PActor>& get_all_actors() { return actors_; }
		void add_actor(shared_ptr<Actor> actor);
		void remove_actor(shared_ptr<Actor> actor);
		void remove_actor(idtype id);
		
		const string& get_name() { return name_; }
		void set_name(const string& name) { name_ = name; }


	private:
		string name_{"empty-world"};

		vector<PActor> actors_;

		hashtable<idtype, size_t> id2actors_;
	};
}


