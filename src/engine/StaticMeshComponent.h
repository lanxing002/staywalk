#pragma once
#include "Common.h"
#include "GameComponent.h"
#include "RenderObject.h"
namespace staywalk{
	class StaticMeshComponent : public GameComponent{
	public:
		virtual void draw();

	private:
		vector<PRMesh> meshs_;
	};
}


