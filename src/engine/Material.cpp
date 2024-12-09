#include "Material.h"
#include "Utility.h"

namespace staywalk {
	const string Material::DiffuseKey = "diffuse";
	const string Material::AoKey = "ao";

	Material::Material(const string& name)
		: Object(name) {
	}

	Material::~Material(){
		if (program_) RProgram::monitor(program_, false);
	}

	void Material::add_tex(const string& name, RTexRef tex){
		if (tex == nullptr) return;
		bool added = false;
		for (auto& [n, t] : texs_) {
			if (n == name) {
				t = tex;
				added = true;
				break;
			}
		}

		if (!added) texs_.emplace_back(name, tex);
	}

	void Material::add_uniform(const string& name, UniformRef uniform){
		if (uniform == nullptr) return;
		bool added = false;
		for (auto& [n, u] : uniforms_) {
			if (n == name) {
				u = uniform;
				added = true;
				break;
			}
		}
		if (!added) uniforms_.emplace_back(name, uniform);
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
					if (it1->second->name_ != it2->second->name_) return false;
				}
				else return false;
			}
		}

		return true;
	}

	void Material::use(RenderInfo info){
		if (program_) {
			program_->use();
			program_->set_uniform("view", info.view_.top());
			program_->set_uniform("projection", info.projection_.top());
			program_->set_uniform("model", info.model_.top());

			for (auto& [n, u] : uniforms_) {
				if (u)
					program_->set_uniform(name_, u);
			}

			int idx = 0;
			for (auto& [n, t] : texs_) {
				if(t == nullptr) continue;
				auto texid = t->get_updated_glid();
				if (texid == kGlSickId) continue;;
				glActiveTexture(GL_TEXTURE0 + idx);
				glBindTexture(GL_TEXTURE_2D, texid);
				program_->set_uniform(n, idx);
				idx++;
			}
		}
	}
}