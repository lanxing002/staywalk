#pragma once
#include "Common.h"
#include "GameComponent.h"
#include "RenderObject.h"
namespace staywalk{
	class sw_Class StaticMeshComponent : public GameComponent {
	public:
		sw_Func virtual void draw();

		sw_Prop vector<PRMesh> meshs;
	};
}


