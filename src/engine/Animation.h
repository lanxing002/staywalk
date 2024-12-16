#pragma once
#include "Entity.h"
#include "RMesh.h"

namespace staywalk {
	class AnimationLoader;

	class sw_Class() BoneTreeNode : public Object
	{
	public:
		sw_Prop(nogui;) mat4 transform_;
		sw_Prop(nogui;) vector<BoneTreeNode> children_;
		sw_Prop(nogui;) int bone_id_;
		MetaRegister(BoneTreeNode);
	};

	class sw_Class(jsonpost;) Animation : public RObject {
	public:
		sw_Func() Animation(const string & name = "0-animation");
		MetaRegister(Animation);

		void animate(float delta);
		void gl_delete();
		GLuint get_updated_glid();

	private:
		mat4 calculate_per_bone(const Bone& bone);
		void calculate_bone_transform(const BoneTreeNode& node, mat4 parentTransform);
		void gl_update();
		void load_post();
		void dump_post() const;

	private:
		sw_Prop() float curr_time_;
		sw_Prop() float duration_;
		sw_Prop() float ticks_pers_;  // per second 
		sw_Prop() BoneTreeNode node_root_;
		sw_Prop(nogui; nojson;) vector<Bone> bones_;
		std::array<mat4, staywalk::kMaxBoneNum> bone_influences_;
		friend class SkeletonMeshLoader;
	};
}


