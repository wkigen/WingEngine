#include "texture.h"
#include "renderer_system.h"

namespace WingEngine
{
	Texture::Texture(Image* image)
	{
		if (image)
		{
			mImage = image;
			mColorFormat = image->getColorFormat();
			mWidth = image->getWidth();
			mHeight = image->getHeight();
			mDataElementType = DataElementUByte;
			switch (image->getColorFormat())
			{
			case ColorFormatRGB:
				mTextureType = TextureTypeRGB;
				mTextureFormat = TextureFormatRGB;
				break;
			case ColorFormatRGBA:
				mTextureType = TextureTypeRGBA;
				mTextureFormat = TextureFormatRGBA;
				break;
			default:
				mTextureType = TextureTypeRGBA;
				mTextureFormat = TextureFormatRGBA;
				break;
			}
			
		}
	}

	Texture::Texture(uint32 width, uint32 height, TextureType textureType, TextureFormat textureFormat, ColorFormat colorFormat, DataElementType dataElementType)
	{
		mWidth = width;
		mHeight = height;
		mTextureType = textureType;
		mColorFormat = colorFormat;
		mTextureFormat = textureFormat;
		mDataElementType = dataElementType;
	}

	Texture::~Texture()
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		context->deleteTexture(mGPUBufferId);
	}

	void Texture::bindGPUBuffer() 
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();

		if (mImage)
		{
			mGPUBufferId = context->bindTextureBuffers(mTextureFormat, mWidth,mHeight, mColorFormat, mDataElementType, mImage->getData());
		}
		else
		{
			mGPUBufferId = context->bindTextureBuffers(mTextureFormat,mWidth,mHeight, mColorFormat, mDataElementType ,0);
		}
	
	}
}