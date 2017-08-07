#include "geometry_texture_light_shadow_second_pass.h"
#include "renderer\renderer_system.h"


namespace WingEngine
{


	GeometryTextureLightShadowSecondPass::GeometryTextureLightShadowSecondPass()
	{

	}

	GeometryTextureLightShadowSecondPass::~GeometryTextureLightShadowSecondPass()
	{

	}

	void GeometryTextureLightShadowSecondPass::init()
	{
		BaseRenderPass::init();
	}

	void GeometryTextureLightShadowSecondPass::preRender()
	{
		BaseRenderPass::preRender();

	}

	void  GeometryTextureLightShadowSecondPass::_render(Renderable* renderable)
	{
		BaseRenderPass::_render(renderable);
	}

	void GeometryTextureLightShadowSecondPass::render(Renderable* renderable)
	{
		
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		_render(renderable);
		context->draw(renderable->getIndeiceData()->getDataNum());

	}

	void GeometryTextureLightShadowSecondPass::postRender()
	{
		BaseRenderPass::postRender();
	}

}
