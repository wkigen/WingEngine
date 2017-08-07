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
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		mProgram = RendererSystem::getInstance()->getProgram("shadow_map_first");

		mAttribPosition = context->getAttribLocation(mProgram->getProgramID(), POSITION);
		mUniformModelMatrix = context->getUniformLocation(mProgram->getProgramID(), MODELVIEWMARTIX);
		mUniformProjectdViewMatrix = context->getUniformLocation(mProgram->getProgramID(), PROJECTVIEWMARTIX);
		mUniformViewPosition = context->getUniformLocation(mProgram->getProgramID(), VIEWPOSITION);

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

	void GeometryTextureLightShadowFirstPass::_render(Renderable* renderable)
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		Matrix44 projectMatrix44 = RendererSystem::getInstance()->getCamera()->getmProjectModelMatrix44();
		Vectorf viewPosition = RendererSystem::getInstance()->getCamera()->getPosition();

		context->bindArrayBuffers(renderable->getVertixData()->getGPUBufferId());
		context->bindElementBuffers(renderable->getIndeiceData()->getGPUBufferId());

		//世界矩阵 投影矩阵
		context->setUniformMatrix44f(mUniformModelMatrix, 1, renderable->getModelViewMatrinx44());
		context->setUniformMatrix44f(mUniformProjectdViewMatrix, 1, projectMatrix44);

		context->setUniform3f(mUniformViewPosition, viewPosition);
	}

	void GeometryTextureLightShadowFirstPass::render(Renderable* renderable)
	{
	
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		_render(renderable);
		context->draw(renderable->getIndeiceData()->getDataNum());
	}

	void GeometryTextureLightShadowFirstPass::postRender()
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		context->bindRenderTarget(INVALID_BUFFERS);
	}

}
