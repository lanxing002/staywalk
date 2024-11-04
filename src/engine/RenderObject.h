#pragma once
#include "Object.h"

namespace staywalk{
	// render object is a opengl object
	class RTex : public Object {

	};

	class RMesh : public Object {

	};

	class RShader : public Object {

	};

	class RProgram : public Object{

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
}


