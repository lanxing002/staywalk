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

	enum class sw_Class() GlMagFilter : int {
		NEAREST = GL_NEAREST,
			LINEAR = GL_LINEAR,
	};

	struct Drawable {
	public:
		virtual void draw(RenderInfo& info) = 0;
	};

	static constexpr uint kMaxBoueInfluence = 4;
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

	
	class sw_Class(jsonpost;)  Tex2D : public RObject {
	public:
		Tex2D(const string& name = "tex-0");
		//sw_Prop() Tex2d tex;
		sw_Prop() bool mipmap = true;
		sw_Prop() GlWrap wrap_s = GlWrap::REPEAT;
		sw_Prop() GlWrap wrap_t = GlWrap::REPEAT;
		sw_Prop() GlMinFilter min_filter = GlMinFilter::LINEAR;
		sw_Prop() GlMagFilter mag_filter = GlMagFilter::LINEAR;
		MetaRegister(Tex2D);

		GLuint get_updated_glid();
		void gl_delete();

	private:
		void gl_update();
		void load_post();
		void dump_post() const;

		// texture host memory 
		unsigned char* host_data_ = nullptr;
		int width_ = -1;
		int height_ = -1;
		int nr_comps_ = -1;

		friend class Utility;
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


