#pragma once
#include "RenderObject.h"
#include <map>

namespace staywalk {
	class Material : public Object{
	public:
		static const string DiffuseKey;
		static const string AoKey;

	public:
		Material(shared_ptr<RShader> shader = nullptr, const string& name="0-material");

		void add_tex(const string& name, PRTex tex) { texs_[name] = tex; }
		void add_uniform(const string& name, PUniform uniform) { uniforms_[name] = uniform; }

		ObjectType get_type_value() const override { return ObjectType::Material; }
		bool operator==(const Material& gameobj);
	protected:
		void dump_impl(ofstream& ofs, Dumper& dumper) const override;
		void load_impl(ifstream& ifs, Loader& loader) override;

		shared_ptr<RShader> shader_;
		std::map<string, shared_ptr<RUniform>> uniforms_;
		std::map<string, shared_ptr<RTex>> texs_;
	};
}


