#include "World.h"
#include "Actor.h"

namespace staywalk{
	shared_ptr<World> World::create_empty_world(){
		return shared_ptr<World>();
	}
	
	shared_ptr<World> World::load_marry_world(){
		shared_ptr<Actor> actor = std::make_shared<Actor>("marry");
		return shared_ptr<World>();
	}

	World::~World(){
	}

	shared_ptr<Actor> World::create_actor(){
		return shared_ptr<Actor>();
	}

	void World::destory_actor(shared_ptr<Actor>& actor){
	}
}

