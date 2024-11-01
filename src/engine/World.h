#pragma once
#include "Common.h"
namespace staywalk {
	class Object;
	class Actor;

	class World{
	public:
		~World();

		static shared_ptr<World> create_empty_world();
		
		// test, need to serizalize to scene file
		static shared_ptr<World> load_marry_world();

		shared_ptr<Actor> create_actor();

		void destory_actor(shared_ptr<Actor>& actor);

		const vector<shared_ptr<Actor>>& get_all_actors() { return actors_; }
	
	private:
		World() {}

	private:
		vector<shared_ptr<Actor>> actors_;

		hashtable<int64_t, shared_ptr<Actor>> id2actors_;
	};
}


