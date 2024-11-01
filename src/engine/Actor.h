#pragma once
#include "GameObject.h"
#include "StaticMeshComponent.h"
namespace staywalk {
	class Actor : public GameObject{
	public:
		~Actor();

		void tick(float delta) override;
		void set_sm_comp(const shared_ptr<StaticMeshComponent> comp) { sm_comp_ = comp; }

	private:
		Actor();

	private:
		shared_ptr<StaticMeshComponent> sm_comp_{ nullptr };

		friend class World;
	};
}


