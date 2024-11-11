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
		auto meshload = MeshLoader(R"(C:\Users\lanxi\Documents\lanxing\codes\ErJiu\games202-hw\hw1\homework1\assets\mary\Marry.obj)");
		return shared_ptr<World>();
	}

	void World::add_actor(shared_ptr<Actor> actor){
		//if (actor == nullptr) return;
		//auto it = id2actors_.find(actor->get_guid());
		//if (it != id2actors_.end()) {
		//	auto idx = it->second;
		//	actors_[idx] = actor;
		//}
		//else {
		//	id2actors_[actor->get_guid()] = actors_.size();
		//	actors_.push_back(actor);
		//}
	}

	void World::remove_actor(shared_ptr<Actor> actor){
		//if(actor)
			//remove_actor(actor->get_guid());
	}

	void World::remove_actor(idtype id){
		auto it = id2actors_.find(id);
		if (it != id2actors_.end()) {
			actors_.erase(actors_.begin() + it->first);
			id2actors_.erase(it);
		}
	}

	World::~World(){
	}


}

