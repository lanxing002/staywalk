#pragma once

#include "Material.h"


namespace staywalk{
	class sw_Class(jsonpost;)  RMesh : public RObject {
	public:
		sw_Func()  RMesh(const string& name = "mesh-0");

		sw_Func()  RMesh(const vector<Vertex>& vv, const vector<unsigned int>& ii, const string& name = "0-mesh");

		void organize() override;
		void disband() override;
		bool load_resource() override;

	public:
		sw_Prop(nojson;nogui;) vector<Vertex> vertices;
		sw_Prop(nojson;nogui;) vector<unsigned int> indices;
		sw_Prop() shared_ptr<Material> mat;

		uint vbo = kGlSickId;

		MetaRegister(RMesh);

	private:
		void load_post();
		void dump_post() const;
	};

	using PRMesh = shared_ptr<RMesh>;
}

