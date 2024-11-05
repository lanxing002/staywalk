#pragma once
#include "Object.h"

namespace staywalk{
	// render object is a opengl object
	static constexpr uint kMaxBoueInfluence = 4;

	struct Vertex {
		vec3 position{.0};
		vec3 normal{0.0};
		vec2 texcoords{.0};
		vec3 tangent{.0};
		vec3 bitangent{.0};
		//bone indexes which will influence this vertex
		
		array<int, kMaxBoueInfluence> boune_ids;
		array<float, kMaxBoueInfluence> weights;
	};

	class RObject : public Object{

	public:
		uint glid = kGlInvalidId;  // for opgnel id, -1 is invalid
		bool valid = false;
		string path;
	};

	class RTex : public RObject {

	};

	class RMesh : public RObject {

	};

	class RShader : public RObject {

	};

	class RProgram : public RObject {

	};


	// resource file use for cpu side, for create render object and edit
	class Resource : public Object {
	public:
		const bool editable = false;
	};

	class Shader : public Resource {
	public:
		const bool editable = true;
	};

	class Tex2d : public Resource {
	public:
		const bool editable = false;
	};
	using PRObject = shared_ptr<RObject>;
	using PRTex = shared_ptr<RTex>;
	using PRMesh = shared_ptr<RMesh>;
	using PRShader = shared_ptr<RShader>;
	using PRProgram = shared_ptr<RProgram>;
}


