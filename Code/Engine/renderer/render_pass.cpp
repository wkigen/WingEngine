#include "render_pass.h"
#include "renderable.h"

namespace WingEngine
{


	RenderPass::RenderPass(Renderable* renderable)
		:mRenderable(renderable)
	{
	}

	RenderPass::~RenderPass()
	{

	}
}