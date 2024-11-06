#pragma once
#include "GameObject.h"
#include "StaticMeshComponent.h"
#include "Utility.h"
namespace staywalk {
	class Actor : public GameObject, public DumpLoad<Actor>{
	public:
		Actor(const string& name = "0-actor");

		void tick(float delta) override;

		ObjectType get_type_value() override { return ObjectType::Actor; }
		void set_sm_comp(const shared_ptr<StaticMeshComponent> comp) { sm_comp_ = comp; }

		bool operator==(const Actor& gameobj);
	protected:
		void dump_impl(ofstream& ofs, Dumper& dumper);
		static void load_impl(shared_ptr<Actor> obj, ifstream& ifs, Loader& loader);

	private:
		shared_ptr<StaticMeshComponent> sm_comp_{ nullptr };

		friend class World;
	};

	using PActor = shared_ptr<Actor>;
}


