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

		void initialize_post();

		void destroy() override;

		void render(double delta, unsigned long long count) override;

	private:
		void render_main();

		void render_post_bloom();
		
		void render_post1();

		void render_post_tone_mapping();

		void render_screen();

		void render_custom_rt(RenderTargetRef rt);

		// render all meshes, for render target or main pass
		void render_all_mesh(RenderInfo& render_info);

		void init_screen_source();

	private:
		// render pipeline start
		ivec2 view_size_;

		// mainpass
		Ref<GBuffer> mainpass_gbuffer_;
		RenderTargetRef mainpass_fb_;

		// post pass
		RenderTarget2DRef post_front_;   // just color
		RenderTarget2DRef post_back_;	  // just color	 

		CSProgramRef post_bloom_h_cs_;
		CSProgramRef post_bloom_v_cs_;
		RenderTarget2DRef post_bloom_rt_;

		CSProgramRef post_tone_mapping_cs_;

		// render to screen pass
		uint screen_draw_program_ = kGlSickId;
		uint screen_vao_ = kGlSickId;

		// render pipeline end
	};
}