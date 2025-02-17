#pragma once
#include "Common.h"
#include "Component.h"
#include "RMesh.h"

namespace staywalk{
	class sw_Class()  StaticMeshComponent : public Component, public Drawable {
	public:
		sw_Func() StaticMeshComponent(const string & name = "sm-comp-0");
		sw_Func() void add_mesh(MeshRef mesh) {
			if (mesh) meshs.emplace_back(mesh, nullptr); 
		}

		sw_Func() void update_material(idtype id, MaterialRef mat);

		void draw(RenderInfo& info) override;

		void tick(float delta) override {}

		sw_Func() AABB get_aabb() const;

		sw_Prop() vector<pair<MeshRef, MaterialRef>> meshs;

		sw_Prop() Transform transform = Identity;

		MetaRegister(StaticMeshComponent);
	};
}


