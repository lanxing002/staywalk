#pragma once
#include "Common.h"
#include "Renderer.h"
#include "RenderInfo.h"
#include "RenderObject.h"

namespace staywalk {
	class DeferredRenderer : public Renderer {
	public:
		DeferredRenderer();
		~DeferredRenderer();

		void initialize() override;

		void destroy() override;

		void render_main(RenderInfo& renderinfo);

		void render(double delta, unsigned long long count) override;

	private:
		Ref<GBuffer> gbuffer_;
	};
}