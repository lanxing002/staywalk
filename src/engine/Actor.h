#pragma once
#include "GameObject.h"
#include "StaticMeshComponent.h"
namespace staywalk {
	class Actor : public GameObject{
	public:
		Actor();
		Actor(const std::string& name) : name_(name) {}

		~Actor();

		void tick(float delta) override;
		void set_sm_comp(const shared_ptr<StaticMeshComponent> comp) { sm_comp_ = comp; }

		bool operator==(const Actor& gameobj);

		void dump(ofstream& ofstrm) override;
		static shared_ptr<Actor> load(ifstream& ifs);

	protected:
		static void placement_load(shared_ptr<Actor> obj, ifstream& ifs);

	private:
		std::string name_{"none"};
		shared_ptr<StaticMeshComponent> sm_comp_{ nullptr };

		friend class World;
	};
}

