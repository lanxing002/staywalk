#include "Material.h"
#include "Utility.h"

namespace staywalk {
	const string Material::DiffuseKey = "diffuse";
	const string Material::AoKey = "ao";

	Material::Material(const string& name)
		: Object(name) {
	}

	Material::~Material(){
		if (program) RProgram::monitor(program, false);
	}

	bool Material::is_same(Ref<Material> rhs) {
		if (texs_.size() != rhs->texs_.size()) {
			return false;
		}

		auto it1 = texs_.begin();
		auto it2 = rhs->texs_.begin();

		for (; it1 != texs_.end(); ++it1, ++it2) {
			if (it1->first != it2->first) return false;
			if (it1->second || it2->second) {
				if (it1->second && it2->second) {
					if (it1->second->name != it2->second->name) return false;
				}
				else return false;
			}
		}

		return true;
	}

	void Material::use(){
		if(program) program->use();
	}
}