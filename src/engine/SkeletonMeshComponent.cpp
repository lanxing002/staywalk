#include "SkeletonMeshComponent.h"
#include "Material.h"
#include "Utility.h"

namespace staywalk {
	SkeletonMeshComponent::SkeletonMeshComponent(const string& name)
		:GameComponent(name) {
	}


	void SkeletonMeshComponent::draw(RenderInfo& info) {
		info.model_.push(info.model_.top() * transform_.matrix());
		info.program_->set_uniform("model", info.model_.top());
		for (auto& [mesh, mat] : meshs_) {
			if (mat) mat->use(info);
			if (mesh) mesh->draw(info);
		}
		info.model_.pop();
	}
}