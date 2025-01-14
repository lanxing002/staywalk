#pragma once
#include "Entity.h"
#include "Camera.h"
#include "RenderObject.h"
#include "RenderTarget.h"

namespace staywalk {
	class sw_Class(jsonpost;)  DepthRenderTarget : public RenderTarget {
	public:
	 	sw_Func()  DepthRenderTarget(const string& name = "0-actor");
		~DepthRenderTarget();
		MetaRegister(DepthRenderTarget);

		Tex2DRTRef depth_rt_;

		//--------------------------------//
		void bind() override;

		void tick(float delte) override;

	private:
		void dump_post() const;
		void load_post();
	};
}


