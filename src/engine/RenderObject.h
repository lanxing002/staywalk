#pragma once
#include "Object.h"
#include "SimpleType.h"
#define gltype int
#include "glad/glad.h"

namespace staywalk{
	
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

		MetaRegister(RObject);

	protected:
		uint glid = kGlSickId;  // for opgnel id, -1 is invalid
	};

	enum class sw_Class() GlWrap : int {
			CLAMP_TO_EDGE			= GL_CLAMP_TO_EDGE,
			MIRRORED_REPEAT			= GL_MIRRORED_REPEAT,
			REPEAT					= GL_REPEAT,
	};

	enum class sw_Class() GlMinFilter : int {
			NEAREST					= GL_NEAREST,
			LINEAR					= GL_LINEAR,
			NEAREST_MIPMAP_NEAREST	= GL_NEAREST_MIPMAP_NEAREST,
			LINEAR_MIPMAP_NEAREST	= GL_LINEAR_MIPMAP_NEAREST,
			NEAREST_MIPMAP_LINEAR	= GL_NEAREST_MIPMAP_LINEAR,
			LINEAR_MIPMAP_LINEAR	= GL_LINEAR_MIPMAP_LINEAR,
	};

	enum class sw_Class() GlMagFilter : int {
			NEAREST					= GL_NEAREST,
			LINEAR					= GL_LINEAR,
	};

	class sw_Class()  RTex : public RObject {
	public:
		RTex(const string& name = "0-rtex");

		void organize() override;
		void disband() override;
		bool load_resource() override;

	public:
		sw_Prop() Tex2d tex;
		sw_Prop() bool mipmap = true;
		sw_Prop() GlWrap wrap_s = GlWrap::REPEAT;
		sw_Prop() GlWrap wrap_t = GlWrap::REPEAT;
		sw_Prop() GlMinFilter min_filter = GlMinFilter::LINEAR;
		sw_Prop() GlMagFilter mag_filter = GlMagFilter::LINEAR;
		
		MetaRegister(RTex);
	};

	enum class sw_Class()  ShaderType : unsigned char {
		None,
		VS,
		FS,
		CS,
	};

	class sw_Class()  RShader : public RObject {
	public:
		RShader(const string& name = "shader-0");
		sw_Prop() ShaderType shadertype = ShaderType::None;
		sw_Prop() SWCodeRef code;

		MetaRegister(RShader);
	};

	class sw_Class()  RProgram : public RObject {
	public:
		RProgram(const string& name = "program-0");
		sw_Prop() RShader vs;
		sw_Prop() RShader fs;

		MetaRegister(RProgram);
	};


	class sw_Class()  RUniform : public RObject {
	public:

		MetaRegister(RUniform);
	};

	using PRObject = shared_ptr<RObject>;
	using PRTex = shared_ptr<RTex>;
	using PRShader = shared_ptr<RShader>;
	using PRProgram = shared_ptr<RProgram>;
	using PUniform = shared_ptr<RUniform>;
}


