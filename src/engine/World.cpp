#include "World.h"
#include "Actor.h"
#include "Utility.h"
#include "Serialize.h"
#include "Logger.h"
#include "Event.h"

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
		auto meshload = MeshLoader(R"(C:\Users\lanxi\Documents\lanxing\codes\ErJiu\games202-hw\homework0\assets\mary\Marry.obj)");

		shared_ptr<Actor> actor = std::make_shared<Actor>("marry");
		Ref<StaticMeshComponent> sm = std::make_shared<StaticMeshComponent>();
		sm->meshs = meshload.get_meshes();
		actor->sm_comp = sm;
		auto world = std::make_shared<World>();
		world->name_ = "marry-world";
		
		world->add_asset(sm);
		world->add_asset(actor);
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
		Event::World_AssetChanged();
		return world;
	}


	void World::add_actor(shared_ptr<Actor> actor){
		if (actor)
			actors_.push_back(actor);
		else
			log(fmt::format("add_acotr: add nullptr"), LogLevel::Warn);
	}


	void World::remove_actor(idtype id){
		actors_.erase(std::remove_if(actors_.begin(), actors_.end(), 
			[id](Ref<Actor>& a) {return a->get_guid() == id; }));
	}

	void World::add_asset(Ref<Object> obj) {
		if (obj){
			assets_[obj->get_guid()] = obj;
			Event::World_AssetChanged();
		}
	}
	
	void World::remove_asset(idtype id) {
		assets_.erase(id);
		Event::World_AssetChanged();
	}
}

