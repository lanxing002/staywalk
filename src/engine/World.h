#pragma once
#include "Common.h"
#include "Light.h"
#include "Camera.h"

namespace staywalk {
	class Object;
	class Actor;
	class World;

	using PObject = Ref<Object>;
	using PActor = Ref<Actor>;
	using PCamera = Ref<Camera>;
	using PLight = Ref<Light>;

	using PWorld = Ref<World>;

	namespace reflect {
		class Dumper;
		class Loader;
	}

	class sw_Class(nogui; nojson;) World {
	public:
		~World();

		void dump();

		sw_Func() static PWorld create_empty_world(const string& world_name);
		// test, need to serizalize to scene file
		sw_Func() static PWorld load_marry_world();
		sw_Func() static shared_ptr<World> load(const string& name);

		sw_Func() const vector<PActor>& get_actors() { return actors_; }
		sw_Func() const vector<PCamera>& get_cameras() { return cameras_; }
		sw_Func() const vector<PLight>& get_lights() { return lights_; }
		sw_Func() const hashtable<idtype, Ref<Object>>& get_all_objects() { return id2objs_; }

		sw_Func() void stash_object(Ref<Object> obj);

		sw_Func() void add_actor(shared_ptr<Actor> actor);
		sw_Func() void remove_actor(shared_ptr<Actor> actor);
		sw_Func() void remove_actor(idtype id);
		
		sw_Func() const string& get_name() { return name_; }
		sw_Func() void set_name(const string& name) { name_ = name; }

		sw_Func() bool in_world(idtype id) { return id2objs_.find(id) != id2objs_.end(); }

	private:
		string name_{"empty-world"};

		vector<PActor> actors_;
		vector<PLight> lights_;
		vector<PCamera> cameras_;
		vector<PObject> stash_objs_;

		hashtable<idtype, Ref<Object>> id2objs_;

		friend class reflect::Dumper;
		friend class reflect::Loader;
	};
}


