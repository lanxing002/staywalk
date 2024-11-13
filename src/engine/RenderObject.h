#pragma once
#include "Object.h"

namespace staywalk{
	struct Vertex;
	class Material;

	// render object is a opengl object
	class sw_Class RObject : public Object{
	public:
		sw_Func RObject(const string& name = "0-RObj") {}

		sw_Prop uint glid = kGlInvalidId;  // for opgnel id, -1 is invalid
		sw_Prop bool valid = false;
		sw_Prop string path;

		MetaRegister(RObject);
	};


	class sw_Class RTex : public RObject {
	public:
		MetaRegister(RTex);
	};

	class sw_Class RShader : public RObject {
	public:

		MetaRegister(RShader);
	};


	class sw_Class RProgram : public RObject {
	public:

		MetaRegister(RProgram);
	};


	class sw_Class RUniform : public RObject {
	public:

		MetaRegister(RUniform);
	};


	// resource file use for cpu side, for create render object and edit
	class sw_Class Resource : public Object {
	public:
		sw_Func Resource(const string& name = "0-resource");
		
		sw_Prop fs::path source;
		sw_Prop fs::path dump_dir;

		MetaRegister(Resource);
	};

	enum class sw_Class ShaderType : unsigned char{
		None,
		VS,
		FS,
		CS,
	};

	class sw_Class Shader : public Resource {
	public:
		Shader(const string& name = "0-shader");

		sw_Prop string code;
		sw_Prop ShaderType shader_type{ShaderType::None};

		MetaRegister(Shader);
	};

	class sw_Class Tex2d : public Resource {
	public:
		Tex2d(const string& name="0-Tex2d");

		static shared_ptr<Tex2d> MakeTex(fs::path src_path);

		MetaRegister(Tex2d)

	private:
		int width = -1;
		int height;
		int nrComponents;
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
		//bone indexes which will influence this vertex

		//array<int, kMaxBoueInfluence> boune_ids;
		//array<float, kMaxBoueInfluence> weights;
	};

	using PRObject = shared_ptr<RObject>;
	using PRTex = shared_ptr<RTex>;
	using PRShader = shared_ptr<RShader>;
	using PRProgram = shared_ptr<RProgram>;
	using PUniform = shared_ptr<RUniform>;
	using PMaterial = shared_ptr<Material>;
}


