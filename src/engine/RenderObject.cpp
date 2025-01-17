#include "RenderObject.h"
#include "Utility.h"
#include "Material.h"

#include "rhi.h"

namespace staywalk {

	RObject::RObject(const string& name)
		: Object(name) {
	}

	Tex::Tex(const string& name /*= "tex"*/)
		: RObject(name) {
	}

	Tex2D::Tex2D(const string& name)
		: Tex(name) {
	}

	void Tex2D::gl_update() {
		if(glid_ == kGlSickId) glGenTextures(1, &glid_);
		glBindTexture(GL_TEXTURE_2D, glid_);
		glTexImage2D(GL_TEXTURE_2D, 0, (GLint)internal_format_, width_, height_, 0, (GLenum)format_, GL_UNSIGNED_BYTE, host_data_);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint)wrap_s_);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLint)wrap_t_);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLint)min_filter_);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLint)mag_filter_);
		if (mipmap_)glGenerateMipmap(GL_TEXTURE_2D);
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


	void Tex2D::resize(int width, int height){
		if(img_name_.size() > 0)
			log(fmt::format("Tex2D::set_size {}, set size for file texture make no scene", name_), LogLevel::Warn);
		width_ = width;
		height_ = height;
		dirty_ = true;
	}

	void Tex2D::load_post() {
		if (img_name_.size() > 0){  // load from file
			auto status = Utility::load_tex_resource(*this);
			if (status) {
				if (nr_comps_ == 1)
					format_ = GlTexFormat::RED;
				else if (nr_comps_ == 3)
					format_ = GlTexFormat::RGB;
				else if (nr_comps_ == 4)
					format_ = GlTexFormat::RGBA;
			}

			dirty_ = true;
			log(fmt::format("RTex::load_post from {}, status: {}", name_, status),
				status ? LogLevel::Info : LogLevel::Warn);
		}
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

	CubeMap::CubeMap(const string& name /*= "tex-0"*/)
	:Tex(name){
	}

	GLuint CubeMap::get_updated_glid() {
		if (dirty_) {
			gl_update();
			dirty_ = false;
		}
		return glid_;
	}

	void CubeMap::gl_delete() {

	}

	void CubeMap::gl_update() {
		if (host_data_nx_ == nullptr
			|| host_data_ny_ == nullptr
			|| host_data_nz_ == nullptr
			|| host_data_px_ == nullptr
			|| host_data_py_ == nullptr
			|| host_data_pz_ == nullptr) return;

		GLenum format = GL_RED;
		if (nr_comps_ == 1)
			format = GL_RED;
		else if (nr_comps_ == 3)
			format = GL_RGB;
		else if (nr_comps_ == 4)
			format = GL_RGBA;

		glGenTextures(1, &glid_);
		glBindTexture(GL_TEXTURE_CUBE_MAP, glid_);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, format, width_, height_, 0, format, GL_UNSIGNED_BYTE, host_data_px_);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, format, width_, height_, 0, format, GL_UNSIGNED_BYTE, host_data_py_);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, format, width_, height_, 0, format, GL_UNSIGNED_BYTE, host_data_pz_);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, format, width_, height_, 0, format, GL_UNSIGNED_BYTE, host_data_nx_);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, format, width_, height_, 0, format, GL_UNSIGNED_BYTE, host_data_ny_);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, format, width_, height_, 0, format, GL_UNSIGNED_BYTE, host_data_nz_);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, (GLint)wrap_s_);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, (GLint)wrap_t_);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, (GLint)wrap_r_);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, (GLint)min_filter_);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, (GLint)mag_filter_);
	}

	void CubeMap::load_post() {
		auto status = Utility::load_cube_resource(*this);
		dirty_ = true;
		log(fmt::format("CubeMap::load_post from {}, status: {}", name_, status),
			status ? LogLevel::Info : LogLevel::Warn);
	}

	void CubeMap::dump_post() const	{
	}

	RenderTarget2D::RenderTarget2D(const string& name /*= "rt-2d"*/)
	:Tex(name){

	}

	void RenderTarget2D::set_comp_flag(RTComp flag) {
		if (flag != rt_comp_flags_) {
			rt_comp_flags_ = flag;
			dirty_ = true;
		}
	}


	void RenderTarget2D::resize(int width, int height) {
		if (width != width_ || height != height) {
			width_ = width;
			height_ = height;
			dirty_ = true;
		}
	}

	GLuint RenderTarget2D::get_updated_glid() {
		assert(rt_comp_flags_ != RTComp::None);
		if (width_ <= 0 || height_ <= 0) {
			log(fmt::format("RenderTarget::get_updated_glid wrong width {} or height {}", width_, height_),
				LogLevel::Error);
			return kGlSickId;
		}
		if (dirty_) {
			gl_update();
			dirty_ = false;
		}
		return glid_;
	}

	void RenderTarget2D::gl_update(){
		if (glid_ == kGlSickId) glGenFramebuffers(1, &glid_);
		glBindFramebuffer(GL_FRAMEBUFFER, glid_);

		if (rt_comp_flags_ == RTComp::COLOR) {
			if(color_glid_ == kGlSickId) glGenTextures(1, &color_glid_);
			glBindTexture(GL_TEXTURE_2D, color_glid_);
			glTexImage2D(GL_TEXTURE_2D, 0, (GLint)internal_format_, width_, height_, 0, (GLenum)format_, GL_UNSIGNED_BYTE, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLint)min_filter_);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLint)mag_filter_);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_glid_, 0);

			unsigned int attachments[1] = { GL_COLOR_ATTACHMENT0};
			glDrawBuffers(1, attachments);
		}

		if (rt_comp_flags_ == RTComp::DEPTH) {
			if (kGlSickId == depth_glid_) glGenTextures(1, &depth_glid_);
			glBindTexture(GL_TEXTURE_2D, depth_glid_);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width_, height_, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_glid_, 0);
		}
		
		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		GLFBCheck(glid_);
	}

	void RenderTarget2D::bind() {
		glBindFramebuffer(GL_FRAMEBUFFER, get_updated_glid());  // gbuffer
		glViewport(0, 0, width_, height_);
	}

	uint RenderTarget2D::get_color() {
		assert(!dirty_);
		if (rt_comp_flags_ == RTComp::COLOR)
			return color_glid_;
		return kGlSickId;
	}
	uint RenderTarget2D::get_depth() {
		assert(!dirty_);
		if (rt_comp_flags_ == RTComp::DEPTH)
			return depth_glid_;
		return kGlSickId;
	}

	uint RenderTarget2D::get_stencil() {
		assert(!dirty_);
		if (rt_comp_flags_ == RTComp::STENCIL)
			return stencil_glid_;
		return kGlSickId;
	}

	uint RenderTarget2D::get_depth_stencil() {
		assert(!dirty_);
		//if ((rt_comp_flags_ & (int)RTComp::STENCIL) > 0 && (rt_comp_flags_ & (int)RTComp::DEPTH) > 0)
		//	return depth_stencil_glid_;
		return kGlSickId;
	}

	FrameBuffer::FrameBuffer(const string& name /*= "framebuffer"*/)
	:RObject(name){
	}

	GLuint FrameBuffer::get_updated_glid(){
		if (dirty_) { gl_update(); dirty_ = false; }
		return glid_;
	}

	void FrameBuffer::gl_update() {
		gl_delete();
		glGenFramebuffers(1, &glid_);
	}


	GBuffer::GBuffer() 
		:RObject("gbuffer") {
	}

	GLuint GBuffer::get_updated_glid() {
		if (dirty_) {
			gl_update();
			dirty_ = false;
		}
		return glid_;
	}
	
	void GBuffer::set_size(int width, int height) {
		assert(width > 0 && height > 0);
		if (width_ != width || height_ != height) {
			width_ = width;
			height_ = height;
			mark_dirty();
		}
	}

	void GBuffer::bind(){
		glBindFramebuffer(GL_FRAMEBUFFER, get_updated_glid());  // gbuffer
		glViewport(0, 0, width_, height_);
	}

	//GlWrap wrap_s_ = GlWrap::REPEAT;
	//GlWrap wrap_t_ = GlWrap::REPEAT;
	//GlMinFilter min_filter_ = GlMinFilter::LINEAR;
	//GlMagFilter mag_filter_ = GlMagFilter::LINEAR;
	//GlTexFormat format_ = GlTexFormat::RGBA;

	void GBuffer::gl_update() {
		if(glid_ == kGlSickId) glGenFramebuffers(1, &glid_);
		glBindFramebuffer(GL_FRAMEBUFFER, glid_);

		// position color buffer
		glGenTextures(1, &pos_glid_);
		glBindTexture(GL_TEXTURE_2D, pos_glid_);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width_, height_, 0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pos_glid_, 0);
		
		// normal color buffer
		glGenTextures(1, &normal_glid_);
		glBindTexture(GL_TEXTURE_2D, normal_glid_);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width_, height_, 0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, normal_glid_, 0);
		// color + specular color buffer
		
		glGenTextures(1, &albedo_glid_);
		glBindTexture(GL_TEXTURE_2D, albedo_glid_);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, albedo_glid_, 0);

		unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
		glDrawBuffers(3, attachments);

		// depth is render buffer, should not use in shader ??
		glGenRenderbuffers(1, &depth_glid_);
		glBindRenderbuffer(GL_RENDERBUFFER, depth_glid_);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width_, height_);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_glid_);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		GLFBCheck(glid_);

		// wrap mode is defualt
	}
}