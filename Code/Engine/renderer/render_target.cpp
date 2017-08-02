#include "render_target.h"
#include "renderer_system.h"

namespace WingEngine
{

	RenderTarget::RenderTarget()
		:mAttachmentPoint(AttachmentPointColor0)
	{

	}

	RenderTarget::RenderTarget(Texture* texture)
		:mTexture(texture)
		,mAttachmentPoint(AttachmentPointColor0)
	{

	}

	RenderTarget::~RenderTarget()
	{

	}

	void RenderTarget::bindGPUBuffer()
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		mTargetId = context->bindRenderTarget(mAttachmentPoint, mTexture->getTextureType(), mTexture->getWidth(), mTexture->getHeight(), mTexture->getGPUBufferId());
	}

}