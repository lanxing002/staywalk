#include "World.h"
#include "Actor.h"
#include "Utility.h"
#include "Serialize.h"
#include "Logger.h"

namespace staywalk{
	World::~World() {
	}

	void World::dump() {
		auto world_file = Utility::get_worlds_dir() / (get_name() + Utility::kWorldExt);
		ofstream ofs(world_file, std::ios::out | std::ios::binary | std::ios::trunc);
		auto check_r = Utility::check_ofstream(ofs);
		auto dumper = reflect::Dumper(Utility::get_objects_dir());
		dumper.write(actors_, ofs);
		dumper.clear();
		ofs.close();
	}

	PWorld World::create_empty_world(const string& world_name){
		auto world = std::make_shared<World>();
		world->set_name(world_name);
		return world;
	}
	
	PWorld World::load_marry_world(){
		shared_ptr<Actor> actor = std::make_shared<Actor>("marry");
		auto meshload = MeshLoader(R"(E:\gly\codes\LearnOpenGL\resources\objects\backpack\backpack.obj)");
		return shared_ptr<World>();
	}

	shared_ptr<World> World::load(const string& name)
	{
		auto world = std::make_shared<World>();
		auto world_file = Utility::get_worlds_dir() / (name + Utility::kWorldExt);
		if (!fs::exists(world_file)) {
			log(LogLevel::Error, fmt::format("cannot open world file: {}", fs::absolute(world_file).u8string()));
			return nullptr;
		}

		ifstream ifs(world_file, std::ios::in | std::ios::binary);
		auto check_r = Utility::check_ifstream(ifs);
		auto loader = reflect::Loader(Utility::get_objects_dir());
		loader.read(world->actors_, ifs);
		return world;
	}

	void World::add_actor(shared_ptr<Actor> actor){
		if (actor == nullptr) return;
		auto it = id2actors_.find(actor->get_guid());
		if (it != id2actors_.end()) {
			auto idx = it->second;
			actors_[idx] = actor;
		}
		else {
			id2actors_[actor->get_guid()] = actors_.size();
			actors_.push_back(actor);
		}
	}

	void World::remove_actor(shared_ptr<Actor> actor){
		if(actor)
			remove_actor(actor->get_guid());
	}

	void World::remove_actor(idtype id){
		auto it = id2actors_.find(id);
		if (it != id2actors_.end()) {
			actors_.erase(actors_.begin() + it->first);
			id2actors_.erase(it);
		}
	}
}

