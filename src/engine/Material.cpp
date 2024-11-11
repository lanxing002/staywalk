#include "Material.h"
#include "Utility.h"

namespace staywalk {
	const string Material::DiffuseKey = "diffuse";
	const string Material::AoKey = "ao";

	Material::Material(shared_ptr<RShader> shader, const string& name)
		: Object(name), shader_(shader) {
	}

}