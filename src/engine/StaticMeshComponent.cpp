#include "StaticMeshComponent.h"

void staywalk::StaticMeshComponent::draw(){
}
namespace staywalk {
	bool StaticMeshComponent::operator==(const StaticMeshComponent& rhs) {
		if (!GameComponent::operator==(*this)) return false;
		return true;
	}
}