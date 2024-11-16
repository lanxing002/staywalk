#include "RenderObject.h"
#include "Utility.h"
#include "Material.h"

namespace staywalk {
	Resource::Resource(const string& name)
		:Object(name){
	}

	Shader::Shader(const string& name)
		:Resource(name){
	}

	Tex2d::Tex2d(const string& name)
		:Resource(name){
	}

	RObject::RObject(const string& name)
		: Object(name) {
	}
	RTex::RTex(const string& name)
		:RObject(name){
	}

	void RTex::organize() {
		if (!load_resource()) return;
		
		GLenum format;
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
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);

	}
	
	void RTex::disband(){
		glDeleteTextures(1, &glid);
		glid = kGlSickId;
	}

	bool RTex::load_resource(){
		if (nullptr != tex.data) return false;
		return Utility::load_tex_resource(*this);
	}
}