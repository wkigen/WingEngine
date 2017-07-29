#ifndef _WING_ENGINE_IMAGE_H_
#define _WING_ENGINE_IMAGE_H_

#include "resource.h"

namespace WingEngine
{
	class WING_ENGINE_API Image :public Resource
	{
		
	public:

		RESOURCE_TYPE(ResourceTypeImage)

		Image();
		~Image();

		void* createData(uint8 bit, ColorFormat colorType,uint64 width, uint64 height);
		void* getData();

		uint64 getWidth();
		uint64 getHeight();

		ColorFormat getColorFormat() { return mColorFormat; }

	private:
		void* mData;
		uint64 mHeight;
		uint64 mWidth;
		uint8 mBit;
		ColorFormat mColorFormat;
	};
}


#endif