#include "World.h"
#include "Actor.h"
#include "Utility.h"

namespace staywalk{
	PWorld World::create_empty_world(){
		return shared_ptr<World>();
	}
	
	PWorld World::load_marry_world(){
		shared_ptr<Actor> actor = std::make_shared<Actor>("marry");
		Utility::load_model(R"(C:\Users\lanxi\Documents\lanxing\codes\ErJiu\games202-hw\hw1\homework1\assets\mary\Marry.obj)");
		return shared_ptr<World>();
	}

	World::~World(){
	}

	PActor World::create_actor(){
		return shared_ptr<Actor>();
	}

	void World::destory_actor(PActor& actor){
	}
}

