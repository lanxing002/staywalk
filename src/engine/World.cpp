#include "World.h"
#include "Actor.h"
#include "StaticMeshComponent.h"
#include "Utility.h"
#include "Serialize.h"
#include "Logger.h"
#include "Event.h"
#include "Engine.h"

namespace staywalk{
	World::~World() {
	}

	void World::dump() {
		auto world_file = Utility::get_worlds_dir() / (get_name() + Utility::kWorldExt);
		auto dumper = reflect::Dumper(world_file);
		dumper.dump_world(*this);
	}

	WorldRef World::create_empty_world(const string& world_name){
		auto world = std::make_shared<World>();
		world->set_name(world_name);
		auto a1 = std::make_shared<Actor>("actor 1");
		auto a2 = std::make_shared<Actor>("actor 2");
		world->add_actor(a1);
		world->add_actor(a2);
		return world;
	}
	
	WorldRef World::load_marry_world(){
		auto meshload = MeshLoader(R"(E:\gly\codes\LearnOpenGL\resources\objects\rock\rock.obj)", true);

		shared_ptr<Actor> actor = std::make_shared<Actor>("rock");
		Ref<StaticMeshComponent> sm = std::make_shared<StaticMeshComponent>();
		sm->meshs = meshload.get_meshes();
		actor->sm_comp_ = sm;
		auto world = std::make_shared<World>();
		world->name_ = "rock-world";
		
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
		if (world->cameras_.size() > 0 && world->cameras_[0]) {
			world->activate_camera(world->cameras_[0]->get_guid());
		}
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

	void World::add_camera(CameraRef camera){
		if (camera == nullptr) return;
		auto cid = camera->get_guid();
		auto it = find_if(cameras_.begin(), cameras_.end(), [cid](CameraRef& cam) {return cam->get_guid() == cid; });

		cameras_.push_back(camera);
	}

	void World::remove_camera(idtype cid){
		auto it = find_if(cameras_.begin(), cameras_.end(), [cid](CameraRef& cam) {return cam->get_guid() == cid; });
		if (it != cameras_.end()) cameras_.erase(it);
	}

	void World::activate_camera(idtype cid){
		auto it = find_if(cameras_.begin(), cameras_.end(), [cid](CameraRef& cam) {return cam->get_guid() == cid; });
		if (it != cameras_.end()) {
			activate_camera_ = *it;
			camera_dirty_ = true;
		}
	}

	void World::add_light(LightRef light) {
		if (light == nullptr) return;
		auto lid = light->get_guid();
		auto it = find_if(lights_.begin(), lights_.end(), [lid](LightRef& lig) {return lig->get_guid() == lid; });
		if (it != lights_.end()) {
			lights_.push_back(light);
			light_dirty_ = true;
		}
	}
	
	void World::remove_light(idtype lid) {
		auto it = find_if(lights_.begin(), lights_.end(), [lid](LightRef& lig) {return lig->get_guid() == lid; });
		if (it != lights_.end()) {
			lights_.erase(it);
			light_dirty_ = true;
		}
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

	void World::logic_update(float delta){
		for (auto& cam : cameras_) {
			if (cam) cam->tick(delta);
		}

		for (auto& actor : actors_) {
			if (actor) actor->tick(delta);
		}

		for (auto& light : lights_) {
			if (light) light->tick(delta);
		}
	}
}

