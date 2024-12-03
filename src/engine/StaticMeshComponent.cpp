#include "StaticMeshComponent.h"
#include "Material.h"
#include "Utility.h"

namespace staywalk {
	StaticMeshComponent::StaticMeshComponent(const string& name)
		:GameComponent(name) {
	}

	void StaticMeshComponent::draw(RenderInfo& info) {
		auto mat_backup = info.model;
		info.model = info.model * transform.matrix();
		info.program->set_uniform("model", info.model);
		for (auto& [mesh, mat] : meshs) {
			if(mat) mat->use();
			if(mesh) mesh->draw(info);
		}
		info.model = mat_backup;
	}

	AABB StaticMeshComponent::get_aabb() const{
		auto mat = transform.matrix();
		AABB aabb;
		for (auto& [mesh, _] : meshs) {
			if (!mesh)  continue;
			auto m_aabb = mesh->get_aabb();
			aabb.expand(mat * vec4(m_aabb.min, 1.0));
			aabb.expand(mat * vec4(m_aabb.max, 1.0));
		}
		return aabb;
	}
}