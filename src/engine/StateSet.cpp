#include "StateSet.h"
#include "Utility.h"

namespace staywalk {
	const string StateSet::DiffuseKey = "diffuse";
	const string StateSet::AoKey = "ao";

	StateSet::StateSet(const string& name)
		: Object(name) {
	}

	StateSet::~StateSet(){
	}

	void StateSet::add_tex(const string& name, TexRef tex){
		texs_[name] = tex;
	}


	void StateSet::add_uniform(const string& name, UniformRef uniform){
		uniforms_[name] = uniform;
	}

	int StateSet::get_tex_slot(const string& name) {
		auto it = tex_slot_.find(name);
		if (it != tex_slot_.end()) return it->second;
		return -1;
	}


	bool StateSet::is_same(StateSetRef rhs) {
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

	void StateSet::use(ProgramRef program, int tex_slot_bias){
		assert(program);
		for (auto& [n, u] : uniforms_) {
			if (u) program->set_uniform(n, u);
		}

		int idx = tex_slot_bias;
		for (auto& [n, t] : texs_) {
			if (t == nullptr) continue;
			auto texid = t->get_updated_glid();
			if (texid == kGlSickId) continue;;
			program->set_uniform(n, idx);
			tex_slot_[n] = idx;
			glActiveTexture(GL_TEXTURE0 + idx);
			glBindTexture(GL_TEXTURE_2D, texid);
			idx++;
		}
	}
}