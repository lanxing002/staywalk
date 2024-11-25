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
		auto dumper = reflect::Dumper(world_file);
		dumper.dump_world(*this);
	}

	PWorld World::create_empty_world(const string& world_name){
		auto world = std::make_shared<World>();
		world->set_name(world_name);
		auto a1 = std::make_shared<Actor>("actor 1");
		auto a2 = std::make_shared<Actor>("actor 2");
		world->add_actor(a1);
		world->add_actor(a2);
		return world;
	}
	
	PWorld World::load_marry_world(){
		auto meshload = MeshLoader(R"(E:\gly\codes\LearnOpenGL\resources\objects\backpack\backpack.obj)");

		shared_ptr<Actor> actor = std::make_shared<Actor>("marry");
		Ref<StaticMeshComponent> sm = std::make_shared<StaticMeshComponent>();
		sm->meshs = meshload.get_meshes();
		actor->sm_comp = sm;
		auto world = std::make_shared<World>();
		world->name_ = "marry-world";
		world->add_actor(actor);
		return world;
	}

	shared_ptr<World> World::load(const string& name)
	{
		auto world = std::make_shared<World>();
		auto world_file = Utility::get_worlds_dir() / (name + Utility::kWorldExt);
		auto loader = reflect::Loader(world_file);
		loader.load(*world);
		world->set_name(name);
		return world;
	}

	void World::stash_object(Ref<Object> obj) {
		if (obj) {
			auto it = id2objs_.find(obj->get_guid());
			if (it != id2objs_.end()) {
				id2objs_[obj->get_guid()] = obj;
				stash_objs_.push_back(obj);
			}
			else
				log(fmt::format("objet {} had been stashed"), LogLevel::Warn);
		}
	}

	void World::add_actor(shared_ptr<Actor> actor){
		if (actor == nullptr) return;
		if (actor->get_meta_info().tname != "staywalk::Actor")
			return;

		auto it = id2objs_.find(actor->get_guid());
		if (it == id2objs_.end()) {
			actors_.push_back(actor);
			id2objs_[actor->get_guid()] = actor;
		}
	}

	void World::remove_actor(shared_ptr<Actor> actor){
		if(actor)
			remove_actor(actor->get_guid());
	}

	void World::remove_actor(idtype id){
		auto it = id2objs_.find(id);
		if (it != id2objs_.end()) {
			id2objs_.erase(it);
		}
		actors_.erase(std::remove_if(actors_.begin(), actors_.end(), 
			[id](Ref<Actor>& a) {return a->get_guid() == id; }));
	}
}

