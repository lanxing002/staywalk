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

		void render_main();

		void render_post0();
		
		void render_post1();

		void render_screen();

		void render_custom_rt(RenderTargetRef rt);

		void render(double delta, unsigned long long count) override;

		// render all meshes, for render target or main pass
		void render_all_mesh(RenderInfo& render_info);

	private:
		// render pipeline start

			// mainpass
			Ref<GBuffer> mainpass_gbuffer_;


			// post pass


			// render to screen pass



		// render pipeline end
	};
}