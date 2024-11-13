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


	class sw_Class RMesh : public RObject {
	public:
		sw_Func RMesh(const string& name = "0-rmesh") {}

		sw_Func RMesh(const vector<Vertex>& vv, const vector<unsigned int>& ii, const string& name = "0-mesh") {}
		
		sw_Prop vector<Vertex> vertices_;
		sw_Prop vector<unsigned int> indices_;
		sw_Prop shared_ptr<Material> mat_;

		MetaRegister(RMesh);
	};


	class RShader : public RObject {
	public:
	};


	class RProgram : public RObject {
	public:
	};


	class RUniform : public RObject {
	public:
	};


	// resource file use for cpu side, for create render object and edit
	class sw_Class Resource : public Object {
	public:
		sw_Func Resource(const string& name = "0-resource");
		
		sw_Prop fs::path source;
		sw_Prop fs::path dump_dir;

		MetaRegister(Resource);
	};

	enum class ShaderType : unsigned char{
		None,
		VS,
		FS,
		CS,
	};

	class sw_Class Shader : public Resource {
	public:
		sw_Func Shader(const string& name = "0-shader");

		sw_Prop string code;
		sw_Prop ShaderType shader_type{ShaderType::None};

		MetaRegister(Shader);
	};

	class Tex2d : public Resource {
	public:
		Tex2d(const string& name="0-Tex2d");

		static shared_ptr<Tex2d> MakeTex(fs::path src_path);

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

		//bool operator==(const Vertex& rhs) const {
		//	return position == rhs.position &&
		//		normal == rhs.normal &&
		//		texcoords == rhs.texcoords &&
		//		tangent == rhs.tangent &&
		//		bitangent == rhs.bitangent;
		//}
		//bone indexes which will influence this vertex

		//array<int, kMaxBoueInfluence> boune_ids;
		//array<float, kMaxBoueInfluence> weights;
	};

	using PRObject = shared_ptr<RObject>;
	using PRTex = shared_ptr<RTex>;
	using PRMesh = shared_ptr<RMesh>;
	using PRShader = shared_ptr<RShader>;
	using PRProgram = shared_ptr<RProgram>;
	using PUniform = shared_ptr<RUniform>;
	using PMaterial = shared_ptr<Material>;
}


