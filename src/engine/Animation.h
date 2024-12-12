#pragma once
#include "GameObject.h"
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

		~Animation() {}

	private:
		void load_post();
		void dump_post() const;

	private:
		sw_Prop() float duration_;
		sw_Prop() float ticks_pers_;  // per second 
		sw_Prop() BoneTreeNode node_root_;
		sw_Prop(nogui; nojson;) vector<Bone> bones_;
		friend class SkeletonMeshLoader;
	};
}


