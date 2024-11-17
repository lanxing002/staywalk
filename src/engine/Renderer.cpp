#include "Renderer.h"
#include "rhi.h"

void Renderer::render(double delta, unsigned long long count)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the 
}
