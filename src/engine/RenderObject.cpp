#include "RenderObject.h"
#include "Utility.h"
#include "Material.h"

#include "rhi.h"

namespace staywalk {
	Resource::Resource(const string& name)
		:Object(name){
	}

	Tex2d::Tex2d(const string& name)
		:Resource(name){
	}

	RObject::RObject(const string& name)
		: Object(name) {
	}


	RTex::RTex(const string& name)
		: RObject(name) {
	}

	void RTex::organize() {
		if (!load_resource()) return;
		
		GLenum format = GL_RED;
		if (tex.nr_comps == 1)
			format = GL_RED;
		else if (tex.nr_comps == 3)
			format = GL_RGB;
		else if (tex.nr_comps == 4)
			format = GL_RGBA;

		glGenTextures(1, &glid);
		glBindTexture(GL_TEXTURE_2D, glid);
		glTexImage2D(GL_TEXTURE_2D, 0, format, tex.width, tex.height, 0, format, GL_UNSIGNED_BYTE, tex.data);
		
		if(mipmap)glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint)wrap_s);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLint)wrap_t);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLint)min_filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLint)mag_filter);

	}
	
	void RTex::disband(){
		glDeleteTextures(1, &glid);
		glid = kGlSickId;
	}

	void RTex::load_post() {
		auto status = Utility::load_tex_resource(*this);

		log(fmt::format("RTex::load_post from {}, status: {}", tex.name, status),
			status ? LogLevel::Info : LogLevel::Warn);
	}

	void RTex::dump_post() const {
		// editor cannot modify texture, so need not dump texture file
		// may dump render-target,
	}

	/****************************************/
	/****************************************/
	RLight::RLight() {
		light_buffer.light_count = 0;
	}

	RLight::~RLight() {
		light_buffer.light_count = 0;
	}

	void RLight::sync_to_gpu() {
	}

	void RLight::organize() {

	}

	void RLight::disband() {

	}
}