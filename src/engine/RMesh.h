#pragma once

#include "RenderObject.h"
#include "RenderInfo.h"
#include "SimpleType.h"


namespace staywalk{
	class sw_Class(jsonpost;)  Mesh : public RObject, public Drawable {
	public:
		sw_Func() static MeshRef create_simple_mesh();
		sw_Func() static MeshRef create_plane(int row = 100, int column = 100);

	public:
		sw_Func()  Mesh(const string& name = "mesh-0");
		sw_Func()  Mesh(const vector<Vertex>&vv, const vector<unsigned int>&ii, const string & name = "0-mesh");
		~Mesh();

		void gl_delete();
		void draw(RenderInfo & info) override;

		sw_Func() AABB get_aabb();
		sw_Func() AABB compute_aabb();
		MetaRegister(Mesh);

	public:
		sw_Prop(nojson;nogui;) vector<Vertex> vertices_;
		sw_Prop(nojson;nogui;) vector<unsigned int> indices_;
		uint vbo = kGlSickId;
		uint ebo = kGlSickId;

	private:
		void gl_update();
		void load_post();
		void dump_post() const;

		AABB aabb_;
	};

	class sw_Class(jsonpost;)  SkeletonMesh : public RObject, public Drawable {
	public:
		sw_Func()  SkeletonMesh(const string & name = "smesh-0");
		sw_Func()  SkeletonMesh(const vector<SkinVertex>&vv, const vector<unsigned int>&ii, const string & name = "smesh-0");
		//sw_Func() AABB get_aabb();
		//sw_Func() AABB compute_aabb();
		MetaRegister(SkeletonMesh);

		~SkeletonMesh() {}
		void gl_delete();
		void draw(RenderInfo& info) override {}

	private:
		void gl_update();
		void load_post();
		void dump_post() const;

	public:
		sw_Prop(nojson; nogui;) vector<SkinVertex> vertices_;
		sw_Prop(nojson; nogui;) vector<unsigned int> indices_;
		sw_Prop(nojson; nogui;) vector<mat4> bone_mat_;

	private:
		uint vbo = kGlSickId;
		uint ebo = kGlSickId;
		AABB aabb_;
	};
}

