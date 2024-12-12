#include "SkeletonMeshComponent.h"
#include "Material.h"
#include "Utility.h"

namespace staywalk {
	SkeletonMeshComponent::SkeletonMeshComponent(const string& name)
		:GameComponent(name) {
	}


	//void StaticMeshComponent::draw(RenderInfo& info) {
	//	info.model_.push(info.model_.top() * transform.matrix());
	//	info.program_->set_uniform("model", info.model_.top());
	//	for (auto& [mesh, mat] : meshs) {
	//		if(mat) mat->use(info);
	//		if(mesh) mesh->draw(info);
	//	}
	//	info.model_.pop();
	//}

	//AABB StaticMeshComponent::get_aabb() const{
	//	auto mat = transform.matrix();
	//	AABB aabb;
	//	for (auto& [mesh, _] : meshs) {
	//		if (!mesh)  continue;
	//		auto m_aabb = mesh->get_aabb();
	//		aabb.expand(mat * vec4(m_aabb.min, 1.0));
	//		aabb.expand(mat * vec4(m_aabb.max, 1.0));
	//	}
	//	return aabb;
	//}
}