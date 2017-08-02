#ifndef _WING_ENGINE_COLOR_H_
#define _WING_ENGINE_COLOR_H_

#include "common\engine_defines.h"
#include "base\object.h"
#include "resource\image.h"

namespace WingEngine
{

	class WING_ENGINE_API Texture :public Object
	{

	public:

		Texture(Image* image);
		Texture(uint32 width,uint32 height, TextureType textureType, TextureFormat textureFormat, ColorFormat colorFormat, DataElementType dataElementType);
		~Texture();

		virtual void bindGPUBuffer();
		virtual uint32 getGPUBufferId() { return mGPUBufferId; }

		virtual uint32 getWidth() { return mWidth; }
		virtual uint32 getHeight() { return mHeight; }

		virtual ColorFormat getColorFormat() { return mColorFormat; }

		virtual TextureType getTextureType() { return mTextureType; }

		virtual TextureFormat getTextureFormat() { return mTextureFormat; }

		virtual DataElementType getDataElementType() { return mDataElementType; }
	private:
		uint32			mWidth;
		uint32			mHeight;
		SmartPtr<Image> mImage;
		ColorFormat		mColorFormat;
		TextureFormat	mTextureFormat;
		TextureType		mTextureType;
		uint32			mGPUBufferId;
		DataElementType mDataElementType;
	};

}


#endif