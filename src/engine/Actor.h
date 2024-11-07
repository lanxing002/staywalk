#pragma once
#include "GameObject.h"
#include "StaticMeshComponent.h"
namespace staywalk {
	class Actor : public GameObject{
	public:
		Actor(const string& name = "0-actor");
		void tick(float delta) override;
		void set_sm_comp(const shared_ptr<StaticMeshComponent> comp) { sm_comp_ = comp; }

		ObjectType get_type_value() override { return ObjectType::Actor; }
		bool operator==(const Actor& gameobj);
	protected:
		void dump_impl(ofstream& ofs, Dumper& dumper) override;
		void load_impl(ifstream& ifs, Loader& loader) override;

	private:
		shared_ptr<StaticMeshComponent> sm_comp_{ nullptr };

		friend class World;
	};
	using PActor = shared_ptr<Actor>;
}


