#pragma once
#include "Common.h"
#include "GameComponent.h"
#include "RMesh.h"

namespace staywalk{
	class sw_Class()  StaticMeshComponent : public GameComponent {
	public:
		sw_Func() StaticMeshComponent(const string & name = "0-staticmeshcomp");

		sw_Func(nopy;)  virtual void draw();

		sw_Prop() vector<PRMesh> meshs;

		MetaRegister(StaticMeshComponent);
	};
}


