#pragma once
#include "Material.h"

namespace staywalk{
	class sw_Class RMesh : public RObject {
	public:
		sw_Func RMesh(const string& name = "0-rmesh");

		sw_Func RMesh(const vector<Vertex>& vv, const vector<unsigned int>& ii, const string& name = "0-mesh");

		void organize() override;
		void disband() override;
		bool load_resource() override;

	public:
		sw_Prop vector<Vertex> vertices;
		sw_Prop vector<unsigned int> indices;
		sw_Prop shared_ptr<Material> mat;

		uint vbo;

		MetaRegister(RMesh);
	};

	using PRMesh = shared_ptr<RMesh>;
}

