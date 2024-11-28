#pragma once
#include "Common.h"
#include "Light.h"
#include "Camera.h"

namespace staywalk {
	class Object;
	class Actor;
	class World;

	using ObjectRef = Ref<Object>;
	using ActorRef = Ref<Actor>;
	using CameraRef = Ref<Camera>;
	using LightRef = Ref<Light>;

	using WorldRef = Ref<World>;

	namespace reflect {
		class Dumper;
		class Loader;
	}

	class sw_Class(nogui; nojson;) World {
	public:
		~World();
		
		void dump();

		sw_Func() static WorldRef create_empty_world(const string& world_name);
		sw_Func() static WorldRef load_marry_world();
		sw_Func() static shared_ptr<World> load(const string& name);

		sw_Func() const string& get_name() { return name_; }
		sw_Func() void set_name(const string & name) { name_ = name; }
		
		sw_Func() const vector<ActorRef>& get_actors() { return actors_; }
		sw_Func() const vector<CameraRef>& get_cameras() { return cameras_; }
		sw_Func() const vector<LightRef>& get_lights() { return lights_; }

		sw_Func() void add_actor(shared_ptr<Actor> actor);
		sw_Func() void remove_actor(idtype id);

		sw_Func() void add_camera(CameraRef camera);
		sw_Func() void remove_camera(idtype cid);
		sw_Func() void activate_camera(idtype cid);

		sw_Func() void add_light(LightRef light);
		sw_Func() void remove_light(idtype lid);

		// asset for candidate
		sw_Func() const map<idtype, Ref<Object>>& get_all_assets() { return assets_; }
		sw_Func() void add_asset(Ref<Object> obj);
		sw_Func() void remove_asset(idtype id);

		void logic_update();  // game tick

		void render_update();

	private:
		string name_{"empty-world"};

		vector<ActorRef> actors_;
		vector<LightRef> lights_;
		vector<CameraRef> cameras_;
		map<idtype, Ref<Object>> assets_;

		// render field
		bool light_dirty_{ true };
		bool camera_dirty_{ true };
		CameraRef activate_camera_{nullptr};
		//end render field

		friend class reflect::Dumper;
		friend class reflect::Loader;
	};
}


