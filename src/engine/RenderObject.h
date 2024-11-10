#pragma once
#include "Object.h"
#define PROPERTY 

namespace staywalk{
	struct Vertex;
	class Material;

	// render object is a opengl object
	class RObject : public Object{
	public:
		RObject(const string& name = "0-RObj");

		PROPERTY
		uint glid = kGlInvalidId;  // for opgnel id, -1 is invalid
		bool valid = false;
		string path;

	//	ObjectType get_type_value() const override { return ObjectType::RObject; }
	//	bool operator==(const RObject& gameobj);
	//protected:
	//	void dump_impl(ofstream& ofs, Dumper& dumper) const override;
	//	void load_impl(ifstream& ifs, Loader& loader) override;
	};


	class RTex : public RObject {
	public:
		ObjectType get_type_value() const override { return ObjectType::RTex; }
		bool operator==(const RTex& gameobj);
	protected:
		void dump_impl(ofstream& ofs, Dumper& dumper) const override;
		void load_impl(ifstream& ifs, Loader& loader) override;
	};


	class RMesh : public RObject {
	public:
		RMesh(const string& name = "0-rmesh");

		RMesh(const vector<Vertex>& vv, const vector<unsigned int>& ii, const string& name = "0-mesh");
		
	//	vector<Vertex>& get_vertices() { return vertices_; }
	//	vector<unsigned int>& get_indices() { return indices_; }
	//	shared_ptr<Material> get_material() { return mat_; }
	//	void set_mat(shared_ptr<Material> mat) { mat_ = mat; }

	//	ObjectType get_type_value() const override { return ObjectType::RMesh; }
	//	bool operator==(const RMesh& gameobj);
	//protected:
	//	void dump_impl(ofstream& ofs, Dumper& dumper) const override;
	//	void load_impl(ifstream& ifs, Loader& loader) override;

	//private:
		vector<Vertex> vertices_;
		vector<unsigned int> indices_;
		shared_ptr<Material> mat_;
	};


	class RShader : public RObject {
	public:
		ObjectType get_type_value() const override { return ObjectType::RShader; }
		bool operator==(const RShader& gameobj);
	protected:
		void dump_impl(ofstream& ofs, Dumper& dumper) const override;
		void load_impl(ifstream& ifs, Loader& loader) override;
	};


	class RProgram : public RObject {
	public:
		ObjectType get_type_value() const override { return ObjectType::RProgram; }
		bool operator==(const RProgram& gameobj);
	protected:
		void dump_impl(ofstream& ofs, Dumper& dumper) const override;
		void load_impl(ifstream& ifs, Loader& loader) override;
	};


	class RUniform : public RObject {
	public:
		ObjectType get_type_value() const override { return ObjectType::RUniform; }
		bool operator==(const RUniform& gameobj);
	protected:
		void dump_impl(ofstream& ofs, Dumper& dumper) const override;
		void load_impl(ifstream& ifs, Loader& loader) override;
	};


	// resource file use for cpu side, for create render object and edit
	class Resource : public Object {
	public:
		Resource(const string& name = "0-resource");
		
		void set_dump_dir(const fs::path& p) { dump_dir_ = p; }
		void set_source_path(const fs::path& p) { source_ = p; }
		fs::path get_dump_dir() { return dump_dir_; }
		fs::path get_sour;

		ObjectType get_type_value() const override { return ObjectType::Resource; }
		bool operator==(const Resource& rhs);
	protected:
		void dump_impl(ofstream& ofs, Dumper& dumper) const override;
		void load_impl(ifstream& ifs, Loader& loader) override;

	private:
		fs::path source_;
		fs::path dump_dir_;
	};

	enum class ShaderType : unsigned char{
		None,
		VS,
		FS,
		CS,
	};

	class Shader : public Resource {
	public:
		Shader(const string& name = "0-shader");

		void set_code(ShaderType st, const string& code) { shader_type_ = st; code_ = code; }
		const string& get_code() { return code_; }
		ShaderType get_shader_type() { return shader_type_; }

		ObjectType get_type_value() const override { return ObjectType::Shader; }
		bool operator==(const Shader& rhs);
	protected:
		void dump_impl(ofstream& ofs, Dumper& dumper) const override;
		void load_impl(ifstream& ifs, Loader& loader) override;

		string code_;
		ShaderType shader_type_{ShaderType::None};
	};

	class Tex2d : public Resource {
	public:
		Tex2d(const string& name="0-Tex2d");

		static shared_ptr<Tex2d> MakeTex(fs::path src_path);

		ObjectType get_type_value() const override { return ObjectType::Tex2d; }
		bool operator==(const Tex2d& rhs);
	protected:
		void dump_impl(ofstream& ofs, Dumper& dumper) const override;
		void load_impl(ifstream& ifs, Loader& loader) override;

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
	using PRMesh = shared_ptr<RMesh>;
	using PRShader = shared_ptr<RShader>;
	using PRProgram = shared_ptr<RProgram>;
	using PUniform = shared_ptr<RUniform>;
	using PMaterial = shared_ptr<Material>;
}


