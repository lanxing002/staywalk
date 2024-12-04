#pragma once

#include "RenderObject.h"
#include "RenderInfo.h"
#include "SimpleType.h"


namespace staywalk{
	class sw_Class(jsonpost;)  Mesh : public RObject, public Drawable {
	public:
		sw_Func() static MeshRef create_simple_mesh();

	public:
		sw_Func()  Mesh(const string& name = "mesh-0");
		sw_Func()  Mesh(const vector<Vertex>&vv, const vector<unsigned int>&ii, const string & name = "0-mesh");
		~Mesh();

		void organize() override;
		void disband() override;
		bool load_resource() override;
		void draw(RenderInfo & info) override;

		sw_Func() AABB get_aabb();
		sw_Func() AABB compute_aabb();
		MetaRegister(Mesh);

	public:
		sw_Prop(nojson;nogui;) vector<Vertex> vertices;
		sw_Prop(nojson;nogui;) vector<unsigned int> indices;
		uint vbo = kGlSickId;
		uint ebo = kGlSickId;

	private:
		void disband_impl();
		void load_post();
		void dump_post() const;

		AABB aabb_;
	};
}

