#include "StaticMeshComponent.h"
#include "Material.h"
#include "Utility.h"

namespace staywalk {
	StaticMeshComponent::StaticMeshComponent(const string& name)
		:GameComponent(name) {
	}

	void StaticMeshComponent::update_material(idtype id, MaterialRef mat){
		bool status = false;
		for (auto& [mesh, target] : meshs) {
			if (mesh->get_guid() == id) {
				target = mat;
				status = true;
				return;
			}
		}
		//if (status) log("StaticMeshComponent::update_material success");
	}

	void StaticMeshComponent::draw(RenderInfo& info) {
		info.model.push(info.model.top() * transform.matrix());
		info.program->set_uniform("model", info.model.top());
		for (auto& [mesh, mat] : meshs) {
			if(mat) mat->use(info);
			if(mesh) mesh->draw(info);
		}
		info.model.pop();
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