#include "texture.h"
#include "renderer_system.h"

namespace WingEngine
{
	Texture::Texture(Image* image)
		:mImage(image)
	{

	}

	Texture::~Texture()
	{

	}

	void Texture::bindGPUBuffer() 
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		mGPUBufferId = context->bindTextureBuffers(mImage->getColorFormat(), mImage->getWidth(),
			mImage->getHeight(), mImage->getColorFormat(), mImage->getData());
	}
}