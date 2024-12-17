#include "Material.h"
#include "Utility.h"

namespace staywalk {
	Material::Material(const string& name)
		: StateSet(name) {
	}

	Material::~Material(){
		if (program_) Program::monitor(program_, false);
	}

	void Material::use(RenderInfo info){
		auto prog = program_ == nullptr ? info.program_ : program_;
		info.stateset_->use(prog);
		prog->use();

		prog->set_uniform("view", info.view_.top());
		prog->set_uniform("projection", info.projection_.top());
		prog->set_uniform("model", info.model_.top());

		for (auto& [n, u] : uniforms_) {
			if (u) prog->set_uniform(name_, u);
		}

		int idx = info.stateset_->get_texture_num();
		for (auto& [n, t] : texs_) {
			if (t == nullptr) continue;
			auto texid = t->get_updated_glid();
			if (texid == kGlSickId) continue;

			int activated_idx = idx;
			auto used_idx = info.stateset_->get_tex_slot(n);
			if (used_idx >= 0) idx = used_idx;

			prog->set_uniform(n, activated_idx);
			glActiveTexture(GL_TEXTURE0 + activated_idx);
			glBindTexture(GL_TEXTURE_2D, texid);
			idx++;
		}
	}
}