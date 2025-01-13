#pragma once
#include "Object.h"
#include "RenderInfo.h"
#include "glad/glad.h"

namespace staywalk{
	enum class sw_Class() GlWrap : int {
		CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
		MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
		REPEAT = GL_REPEAT,
	};

	enum class sw_Class() GlMinFilter : int {
			NEAREST = GL_NEAREST,
			LINEAR = GL_LINEAR,
			NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
			LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
			NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
			LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR,
		};

	enum class sw_Class() GlTexFormat : int {
				RED = GL_RED,
				RGB = GL_RGB,
				RGBA = GL_RGBA,
				DEPTH = GL_DEPTH_COMPONENT,
				DEPTHSTENCIL = GL_DEPTH_STENCIL,
		};

	enum class sw_Class() GlMagFilter : int {
		NEAREST = GL_NEAREST,
			LINEAR = GL_LINEAR,
	};

	struct Drawable {
	public:
		virtual void draw(RenderInfo& info) = 0;
	};

	struct Vertex {
		vec3 position_;
		vec3 normal_;
		vec2 texcoords_;
		vec3 tangent_;
		vec3 bitangent_;

		bool operator==(const Vertex& rhs) const {
			return position_ == rhs.position_ &&
				normal_ == rhs.normal_ &&
				texcoords_ == rhs.texcoords_ &&
				tangent_ == rhs.tangent_ &&
				bitangent_ == rhs.bitangent_;
		}
		void dump(rapidjson::Value& value, staywalk::reflect::Dumper& dumper) const;
		void load(rapidjson::Value& value, staywalk::reflect::Loader& loader);
		//bone indexes which will influence this vertex

		//array<int, kMaxBoueInfluence> boune_ids;
		//array<float, kMaxBoueInfluence> weights;
	};

	class SkinVertex {
	public:
		vec3 position_;
		vec3 normal_;
		vec2 texcoords_;
		vec3 tangent_;
		vec3 bitangent_;
		array<int, kMaxBoueInfluence> bone_ids_;
		array<float, kMaxBoueInfluence> bone_weights_;

		bool operator==(const SkinVertex& rhs) const {
			return position_ == rhs.position_ &&
				normal_ == rhs.normal_ &&
				texcoords_ == rhs.texcoords_ &&
				tangent_ == rhs.tangent_ &&
				bitangent_ == rhs.bitangent_ && 
				bone_ids_ == rhs.bone_ids_ &&
				bone_weights_ == bone_weights_;
		}
		void dump(rapidjson::Value& value, staywalk::reflect::Dumper& dumper) const;
		void load(rapidjson::Value& value, staywalk::reflect::Loader& loader);
		//bone indexes which will influence this vertex

		//array<int, kMaxBoueInfluence> boune_ids;
		//array<float, kMaxBoueInfluence> weights;
	};

	// render object is a opengl object
	class sw_Class()  RObject : public Object{
	public:
		sw_Func()  RObject(const string& name = "0-RObj");
		MetaRegister(RObject);

		bool valid() const { return glid_ != kGlSickId; }
		void mark_dirty() { dirty_ = true; }
		bool is_dirty() const { return dirty_; }

	protected:
		GLuint glid_ = kGlSickId;  // for opengl id, -1 is invalid
		bool dirty_ = true;
	};

	
	class sw_Class() Tex : public RObject {
	public:
		MetaRegister(Tex);

		Tex(const string & name = "tex");
		virtual GLuint get_updated_glid() { assert(false); return glid_; }
		virtual void gl_delete() { return; }

		virtual GLenum get_tex_enum() { assert(false); return 0; }

	private:
		virtual void gl_update() { return; }
	};

	class sw_Class(jsonpost;)  Tex2D : public Tex {
	public:
		sw_Func() Tex2D(const string& name = "tex-2d");
		sw_Prop() bool mipmap_ = true;
		sw_Prop() GlWrap wrap_s_ = GlWrap::REPEAT;
		sw_Prop() GlWrap wrap_t_ = GlWrap::REPEAT;
		sw_Prop() GlMinFilter min_filter_ = GlMinFilter::LINEAR;
		sw_Prop() GlMagFilter mag_filter_ = GlMagFilter::LINEAR;
		sw_Prop() string img_name_;
		MetaRegister(Tex2D);

		GLuint get_updated_glid() override;
		void gl_delete() override;
		GLenum get_tex_enum() override { return GL_TEXTURE_2D; }

	private:
		void gl_update() override;
		void load_post();
		void dump_post() const;

		// texture host memory 
		unsigned char* host_data_ = nullptr;
		int width_ = -1;
		int height_ = -1;
		int nr_comps_ = -1;

		friend class Utility;
	};

	// render target will use one texture object in shader
	class sw_Class()  Tex2DRT : public Tex {
	public:
		sw_Func() Tex2DRT(const string& name = "rt-2d");
		
		sw_Prop() GlWrap wrap_s_ = GlWrap::REPEAT;
		sw_Prop() GlWrap wrap_t_ = GlWrap::REPEAT;
		sw_Prop() GlMinFilter min_filter_ = GlMinFilter::LINEAR;
		sw_Prop() GlMagFilter mag_filter_ = GlMagFilter::LINEAR;
		sw_Prop() GlTexFormat format_ = GlTexFormat::RGBA;
		MetaRegister(Tex2DRT);

		GLenum get_tex_enum() override { return GL_TEXTURE_2D; }
		GLuint get_updated_glid() override;
		void gl_delete() override {}

		int width_ = -1;
		int height_ = -1;
	private:
		void gl_update() override;
	};

	//TODO: need to complete : color(imply + depth), depth, stencil, depth + stencil

	class sw_Class()  FrameBuffer : public RObject {
	public:
		FrameBuffer(const string & name = "framebuffer");
		GLuint get_updated_glid();
		void gl_delete() {}

		MetaRegister(FrameBuffer);
	private:
		void gl_update();
	};

	class sw_Class(jsonpost;)  CubeMap : public Tex {
	public:
		sw_Func() CubeMap(const string& name = "cube-map-0");
		sw_Prop() string img_name_;
		sw_Prop() string img_extension_;
		sw_Prop() GlWrap wrap_s_ = GlWrap::CLAMP_TO_EDGE;
		sw_Prop() GlWrap wrap_t_ = GlWrap::CLAMP_TO_EDGE;
		sw_Prop() GlWrap wrap_r_ = GlWrap::CLAMP_TO_EDGE;
		sw_Prop() GlMinFilter min_filter_ = GlMinFilter::LINEAR;
		sw_Prop() GlMagFilter mag_filter_ = GlMagFilter::LINEAR;

		MetaRegister(CubeMap);

		GLenum get_tex_enum() override { return GL_TEXTURE_CUBE_MAP; }
		GLuint get_updated_glid();
		void gl_delete();

	private:
		void gl_update();
		void load_post();
		void dump_post() const;

		// texture host memory 
		unsigned char* host_data_nx_ = nullptr;
		unsigned char* host_data_ny_ = nullptr;
		unsigned char* host_data_nz_ = nullptr;
		unsigned char* host_data_px_ = nullptr;
		unsigned char* host_data_py_ = nullptr;
		unsigned char* host_data_pz_ = nullptr;

		int width_ = -1;
		int height_ = -1;
		int nr_comps_ = -1;

		friend class Utility;
	};

	// will use mulity render target in other shader
	class GBuffer : public RObject {
	public:
		GBuffer();
		GLuint get_updated_glid();
		void gl_delete() {}
		void set_size(int width, int height);

		uint get_pos() { assert(!dirty_); return pos_glid_; }
		uint get_depth() { assert(!dirty_); return depth_glid_; }
		uint get_normal() { assert(!dirty_); return normal_glid_; }
		uint get_albedo() { assert(!dirty_); return albedo_glid_; }
		void bind();

	private:
		int width_ = -1;
		int height_ = -1;

		uint pos_glid_ = kGlSickId;
		uint depth_glid_ = kGlSickId;
		uint normal_glid_ = kGlSickId;
		uint albedo_glid_ = kGlSickId;

		void gl_update();
	};

	// engine use this struct to manage light
	struct RenderLight {
		static constexpr unsigned int kMaxLights = 20;

		struct __LightBlock {
			vec3 position;
			float intensity;
			vec3 color;
			float __padding;
		};

		struct __LightBuffer {
			int light_count;
			std::array<float, 3> __padding;
			std::array<__LightBlock, kMaxLights> light_data;
		};

		void sync_to_gpu();

		void organize();

		void disband();

		__LightBuffer light_buffer;

	private:
		RenderLight();
		~RenderLight();

		uint ubo_ = kGlSickId;
		friend class Renderer;
	};
}


