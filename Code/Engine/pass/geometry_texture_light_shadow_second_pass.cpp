#include "geometry_texture_light_shadow_second_pass.h"
#include "renderer\renderer_system.h"


namespace WingEngine
{


	GeometryTextureLightShadowSecondPass::GeometryTextureLightShadowSecondPass()
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();

		mProgram = RendererSystem::getInstance()->getProgram("shadow_map_second");
	}

	GeometryTextureLightShadowSecondPass::~GeometryTextureLightShadowSecondPass()
	{

	}

	void GeometryTextureLightShadowSecondPass::init()
	{
		BaseRenderPass::init();

		RendererContext* context = RendererSystem::getInstance()->getRendererContext();

		mTexture1 = context->getUniformLocation(mProgram->getProgramID(), TEXTURE1);
		mUniformLightMVPMatrix = context->getUniformLocation(mProgram->getProgramID(), LIGHTMVPMARTRIX);
	}

	void GeometryTextureLightShadowSecondPass::preRender()
	{
		BaseRenderPass::preRender();

		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		
		SmartPtr<Camera> camera = RendererSystem::getInstance()->getCamera();

		real lightMvpMatrix44[MAX_LIGHT * 16];
		int32 count = 0;
		for (uint32 ii = 0; ii < 3 * mLightNum; ii = ii + 3)
		{
			real posX = mLightPostion[ii];
			real posY = mLightPostion[ii + 1];
			real posZ = mLightPostion[ii + 2];

			real dirX = mLightDirection[ii];
			real dirY = mLightDirection[ii + 1];
			real dirZ = mLightDirection[ii + 2];

			Vectorf pos(posX, posY, posZ);
			Vectorf dir(dirX, dirY, dirZ);
			Vectorf up(0.0, 1.0, 0.0);

			Matrix44 lookat = mtxLookAt(pos, dir.normalize(), up);
			SmartPtr<Light> light = RendererSystem::getInstance()->getLight(count);
			Matrix44 vp = lookat * camera->getProjectMatrix44();

			memcpy(lightMvpMatrix44, vp.mData.data, 16 * sizeof(real));

			count++;
		}

		context->setUniformMatrix44f(mUniformLightMVPMatrix, MAX_LIGHT, lightMvpMatrix44);
	}

	void  GeometryTextureLightShadowSecondPass::_render(Renderable* renderable)
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();

		context->setUniform1d(mTexture0, 0);
		context->setUniform1d(mTexture1, 1);

		context->activityTexture(TEXTUREID0);
		BaseRenderPass::_render(renderable);
	
		context->activityTexture(TEXTUREID1);
		context->bindTexture(mDepthTexture->getGPUBufferId());

	}

	void GeometryTextureLightShadowSecondPass::render(Renderable* renderable)
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		_render(renderable);
		context->draw(renderable->getIndeiceData()->getDataNum());
	}

	void GeometryTextureLightShadowSecondPass::postRender()
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		BaseRenderPass::postRender();
		context->activityTexture(TEXTUREID0);
	}

}
