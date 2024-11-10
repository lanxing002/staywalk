#include "StaticMeshComponent.h"
#include "Utility.h"
void staywalk::StaticMeshComponent::draw(){
}
namespace staywalk {
	bool StaticMeshComponent::operator==(const StaticMeshComponent& rhs) {
		if (!GameComponent::operator==(rhs)) return false;
		if (!Utility::equal(meshs_, meshs_)) return false;
		return true;
	}

	void StaticMeshComponent::dump_impl(ofstream& ofs, Dumper& dumper) const {
		GameComponent::dump_impl(ofs, dumper);
		dumper.write_vector(meshs_, ofs);
	}

	void StaticMeshComponent::load_impl(ifstream& ifs, Loader& loader) {
		GameComponent::load_impl(ifs, loader);
		loader.read_vector(meshs_, ifs);
	}
}