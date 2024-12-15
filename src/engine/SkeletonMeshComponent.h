#pragma once
#include "Common.h"
#include "GameComponent.h"
#include "RMesh.h"

namespace staywalk{
	class sw_Class()  SkeletonMeshComponent : public GameComponent, public Drawable {
	public:
		sw_Func() SkeletonMeshComponent(const string & name = "sm-comp-0");
		sw_Func() void update_material(idtype id, MaterialRef mat) {}
		sw_Prop() Transform transform_ = Identity;
		sw_Prop() vector<pair<SkeletonMeshRef, MaterialRef>> meshs_;
		sw_Prop() AnimationRef animation_;
		MetaRegister(SkeletonMeshComponent);

		~SkeletonMeshComponent() override {}
		void draw(RenderInfo& info) override;
		void tick(float delta) override;
	};
}


