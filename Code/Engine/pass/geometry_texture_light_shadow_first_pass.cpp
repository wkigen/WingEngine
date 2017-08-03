#include "geometry_texture_light_shadow_first_pass.h"
#include "renderer\renderer_system.h"
#include "shader\geometry_texture_light_shader.h"

namespace WingEngine
{


	GeometryTextureLightShadowFirstPass::GeometryTextureLightShadowFirstPass(uint32 width, uint32 height)
		:mWidth(width)
		,mHeight(height)
	{

	}

	GeometryTextureLightShadowFirstPass::~GeometryTextureLightShadowFirstPass()
	{

	}

	void GeometryTextureLightShadowFirstPass::init()
	{

		mTexture = WING_NEW Texture(mWidth, mHeight,TextureTypeRGB, TextureFormatRGB, ColorFormatRGB, DataElementUByte);
		mTexture->bindGPUBuffer();
		mRenderTarget = WING_NEW RenderTarget(mTexture);
		mRenderTarget->setAttachmentPoint(AttachmentPointColor0);
		mRenderTarget->bindGPUBuffer();

		mDepthTexture = WING_NEW Texture(mWidth, mHeight, TextureTypeDepth, TextureFormatDepth, ColorFormatDepth, DataElementUInt);
		mDepthTexture->bindGPUBuffer();
		mDepthRenderTarget = WING_NEW RenderTarget(mDepthTexture);
		mDepthRenderTarget->setAttachmentPoint(AttachmentPointDepth);
		mDepthRenderTarget->bindGPUBuffer();
	}

	void GeometryTextureLightShadowFirstPass::preRender()
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();

		context->bindRenderTarget(mRenderTarget->getTargetId());
		context->clear();
	}

	void GeometryTextureLightShadowFirstPass::render(Renderable* renderable)
	{
	
	}

	void GeometryTextureLightShadowFirstPass::postRender()
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		context->bindRenderTarget(INVALID_BUFFERS);
	}

}
