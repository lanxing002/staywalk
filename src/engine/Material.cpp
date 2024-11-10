#include "Material.h"
#include "Utility.h"

namespace staywalk {
	const string Material::DiffuseKey = "diffuse";
	const string Material::AoKey = "ao";

	Material::Material(shared_ptr<RShader> shader, const string& name)
		: Object(name), shader_(shader) {
	}

	bool Material::operator==(const Material& rhs) {
		if (!Object::operator==(rhs)) return false;
		if (!Utility::equal(shader_, rhs.shader_)) return false;
		if (!Utility::equal(uniforms_, rhs.uniforms_)) return false;
		if (!Utility::equal(texs_, rhs.texs_)) return false;
		return true;
	}

	void Material::dump_impl(ofstream& ofs, Dumper& dumper) const {
		Object::dump_impl(ofs, dumper);
		dumper.write_nested_obj(shader_, ofs);
		dumper.write_map(uniforms_, ofs);
		dumper.write_map(texs_, ofs);
	}

	void Material::load_impl(ifstream& ifs, Loader& loader) {
		Object::load_impl(ifs, loader);
		shader_ = pcast<RShader>(loader.read_nested_obj(ifs));
		loader.read_map(uniforms_, ifs);
		loader.read_map(texs_, ifs);
	}
}