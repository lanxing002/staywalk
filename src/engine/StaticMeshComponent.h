#pragma once
#include "Common.h"
#include "GameComponent.h"
#include "RenderObject.h"
namespace staywalk{
	class StaticMeshComponent : public GameComponent{
	public:
		virtual void draw();
		virtual ObjectType get_type_value() { return ObjectType::StaticMeshComponent; }

	private:
		vector<PRMesh> meshs_;
	};
}


