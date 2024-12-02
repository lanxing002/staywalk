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
		vec3 position;
		vec3 normal;
		vec2 texcoords;
		vec3 tangent;
		vec3 bitangent;

		bool operator==(const Vertex& rhs) const {
			return position == rhs.position &&
				normal == rhs.normal &&
				texcoords == rhs.texcoords &&
				tangent == rhs.tangent &&
				bitangent == rhs.bitangent;
		}
		void dump(rapidjson::Value& value, staywalk::reflect::Dumper& dumper) const;
		void load(rapidjson::Value& value, staywalk::reflect::Loader& loader);
		//bone indexes which will influence this vertex

		//array<int, kMaxBoueInfluence> boune_ids;
		//array<float, kMaxBoueInfluence> weights;
	};

	// resource file use for cpu side, for create render object and edit
	class sw_Class()  Resource : public Object {
	public:
		sw_Func()  Resource(const string& name = "0-resource");

		sw_Prop() fs::path source;
		sw_Prop() fs::path dump_dir;

		MetaRegister(Resource);
	};


	class sw_Class()  Tex2d : public Resource {
	public:
		Tex2d(const string& name = "0-Tex2d");

		unsigned char* data = nullptr;
		int width = -1;
		int height = -1;
		int nr_comps = -1;

		MetaRegister(Tex2d)
	};

	// render object is a opengl object
	class sw_Class()  RObject : public Object{
	public:
		sw_Func()  RObject(const string& name = "0-RObj");

		virtual void organize() {}
		virtual void disband() {}
		virtual bool load_resource() { return false; }

		virtual bool valid() { return glid != kGlSickId; }
		virtual void mark_dirty() { dirty_ = true; }
		virtual bool is_dirty() { return dirty_; }

		MetaRegister(RObject);

	protected:
		GLuint glid = kGlSickId;  // for opengl id, -1 is invalid
		bool dirty_ = true;
	};

	
	class sw_Class(jsonpost;)  RTex : public RObject {
	public:
		RTex(const string& name = "tex-0");

		void organize() override;
		void disband() override;

	public:
		sw_Prop() Tex2d tex;
		sw_Prop() bool mipmap = true;
		sw_Prop() GlWrap wrap_s = GlWrap::REPEAT;
		sw_Prop() GlWrap wrap_t = GlWrap::REPEAT;
		sw_Prop() GlMinFilter min_filter = GlMinFilter::LINEAR;
		sw_Prop() GlMagFilter mag_filter = GlMagFilter::LINEAR;
		
		MetaRegister(RTex);

	private:
		void load_post();
		void dump_post() const;
	};

	// engine use this struct to manage light
	struct RLight {
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
		RLight();
		~RLight();

		uint ubo_ = kGlSickId;
		friend class Renderer;
	};
}


