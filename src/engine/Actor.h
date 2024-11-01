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

	private:
		std::string name_{"none"};
		shared_ptr<StaticMeshComponent> sm_comp_{ nullptr };

		friend class World;
	};
}


