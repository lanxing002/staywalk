#include "RenderObject.h"
#include "Utility.h"
#include "Material.h"

#include "rhi.h"

namespace staywalk {
	RObject::RObject(const string& name)
		: Object(name) {
	}


	Tex2D::Tex2D(const string& name)
		: RObject(name) {
	}

	void Tex2D::gl_update() {
		if (host_data_ == nullptr) return;

		GLenum format = GL_RED;
		if (nr_comps_ == 1)
			format = GL_RED;
		else if (nr_comps_ == 3)
			format = GL_RGB;
		else if (nr_comps_ == 4)
			format = GL_RGBA;

		glGenTextures(1, &glid_);
		glBindTexture(GL_TEXTURE_2D, glid_);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width_, height_, 0, format, GL_UNSIGNED_BYTE, host_data_);
		
		if(mipmap_)glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint)wrap_s_);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLint)wrap_t_);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLint)min_filter_);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLint)mag_filter_);
	}
	
	GLuint Tex2D::get_updated_glid(){
		if (dirty_) {
			gl_update();
			dirty_ = false;
		}
		return glid_;
	}

	void Tex2D::gl_delete() {
		glDeleteTextures(1, &glid_);
		glid_ = kGlSickId;
	}

	void Tex2D::load_post() {
		auto status = Utility::load_tex_resource(*this);
		dirty_ = true;
		log(fmt::format("RTex::load_post from {}, status: {}", name_, status),
			status ? LogLevel::Info : LogLevel::Warn);
	}

	void Tex2D::dump_post() const {
		// editor cannot modify texture, so need not dump texture file
		// may dump render-target,
	}

	/****************************************/
	/****************************************/
	RenderLight::RenderLight() {
		light_buffer.light_count = 0;
	}

	RenderLight::~RenderLight() {
		light_buffer.light_count = 0;
	}

	void RenderLight::sync_to_gpu() {
	}

	void RenderLight::organize() {

	}

	void RenderLight::disband() {

	}

}