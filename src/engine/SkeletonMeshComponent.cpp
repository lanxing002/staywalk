#include "SkeletonMeshComponent.h"
#include "Material.h"
#include "Utility.h"
#include "Animation.h"

namespace staywalk {
	SkeletonMeshComponent::SkeletonMeshComponent(const string& name)
		:Component(name) {
	}


	void SkeletonMeshComponent::draw(RenderInfo& info) {
		info.model_.push(info.model_.top() * transform_.matrix());
		info.program_->set_uniform("model", info.model_.top());
		if (animation_) {
			auto bind_idx = info.program_->set_uniform_block("BoneMatrixBlock");
			glBindBufferBase(GL_UNIFORM_BUFFER, 0, animation_->get_updated_glid());
		}

		for (auto& [mesh, mat] : meshs_) {
			if (mat) mat->use(info);
			if (mesh) mesh->draw(info);
		}
		info.model_.pop();
	}

	void SkeletonMeshComponent::tick(float delta){
		if (animation_) animation_->animate(delta);
	}

}