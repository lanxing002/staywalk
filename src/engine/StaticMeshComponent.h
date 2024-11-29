#pragma once
#include "Common.h"
#include "GameComponent.h"
#include "RMesh.h"

namespace staywalk{
	class sw_Class()  StaticMeshComponent : public GameComponent, public Drawable {
	public:
		sw_Func() StaticMeshComponent(const string & name = "sm-comp-0");

		void draw(RenderInfo& info) override;

		sw_Prop() vector<pair<MeshRef, MaterialRef>> meshs;

		sw_Prop() Transform transform = Identity;

		MetaRegister(StaticMeshComponent);
	};
}


