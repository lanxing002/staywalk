#pragma once
#include "Common.h"
#include "GameComponent.h"
#include "RenderObject.h"
namespace staywalk{
	class StaticMeshComponent : public GameComponent {
	public:
		virtual void draw();

		void add_mesh(PRMesh m) { meshs_.push_back(m); }

		void add_meshes(const vector<PRMesh>& ms) { meshs_.insert(meshs_.end(), ms.begin(), ms.end()); }

		vector<PRMesh>& get_meshed() { return meshs_; }

		ObjectType get_type_value() const override { return ObjectType::StaticMeshComponent; }
		bool operator==(const StaticMeshComponent& gameobj);
	protected:
		void dump_impl(ofstream& ofs, Dumper& dumper) const override;
		void load_impl(ifstream& ifs, Loader& loader) override;
		
		vector<PRMesh> meshs_;
	};
}


