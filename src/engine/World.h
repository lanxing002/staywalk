#pragma once
#include "Common.h"

namespace staywalk {
	class Object;
	class Actor;
	class World;

	using PActor = shared_ptr<Actor>;
	using PWorld = shared_ptr<World>;

	class World{
	public:
		~World();

		static PWorld create_empty_world();
		
		// test, need to serizalize to scene file
		static PWorld load_marry_world();

		PActor create_actor();

		void destory_actor(PActor& actor);

		const vector<PActor>& get_all_actors() { return actors_; }
	
	private:
		World() {}

	private:
		vector<PActor> actors_;

		hashtable<int64_t, PActor> id2actors_;
	};
}


