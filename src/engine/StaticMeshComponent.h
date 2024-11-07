#pragma once
#include "Common.h"
#include "GameComponent.h"
#include "RenderObject.h"
namespace staywalk{
	class StaticMeshComponent : public GameComponent{
	public:
		virtual void draw();

		ObjectType get_type_value() override { return ObjectType::StaticMeshComponent; }
		bool operator==(const StaticMeshComponent& rhs);
	private:
		vector<PRMesh> meshs_;
	};
}


