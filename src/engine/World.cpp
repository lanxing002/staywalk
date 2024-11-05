#include "World.h"
#include "Actor.h"
#include "Utility.h"

namespace staywalk{
	PWorld World::create_empty_world(const string& world_name){
		auto world = std::make_shared<World>();
		world->set_name(world_name);
		return world;
	}
	
	PWorld World::load_marry_world(){
		shared_ptr<Actor> actor = std::make_shared<Actor>("marry");
		Utility::load_model(R"(C:\Users\lanxi\Documents\lanxing\codes\ErJiu\games202-hw\hw1\homework1\assets\mary\Marry.obj)");
		return shared_ptr<World>();
	}

	void World::add_actor(shared_ptr<Actor> actor){
		id2actors_[actor->get_guid()] = actors_.size();
		actors_.push_back(actor);
	}

	void World::remove_actor(shared_ptr<Actor> actor){
		auto it = id2actors_.find(actor->get_guid());
		if (it != id2actors_.end()) {
			actors_.erase(actors_.begin() + it->first);
			id2actors_.erase(it);
		}
	}

	void World::remove_actor(idtype id){
	}

	World::~World(){
	}


}

