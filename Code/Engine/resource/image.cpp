#include "image.h"
#include "allocator\allocator.h"

namespace WingEngine
{

	Image::Image()
	{
		mResourceType = ResourceTypeImage;
	}

	Image::~Image()
	{
		WING_FREE(mData);
	}

	void* Image::createData(uint8 bit, ColorFormat colorFormat, uint64 width, uint64 height)
	{
		mBit = bit;
		mWidth = width;
		mHeight = height;
		mColorFormat = colorFormat;

		uint32 _colorFormat;
		switch (colorFormat)
		{
		case ColorFormatRGB:
			_colorFormat = 3;
			break;
		case ColorFormatRGBA:
			_colorFormat = 4;
			break;
		default:
			return nullptr;
			break;
		}

		uint32 _bit;
		switch (bit)
		{
		case 8:
			_bit = 1;
			break;
		default:
			return nullptr;
			break;
		}

		mData = WING_ALLOC(_bit * width * height * _colorFormat);
		
		return mData;
	}

	void* Image::getData()
	{
		return mData;
	}

	uint64 Image::getWidth()
	{
		return mWidth;
	}

	uint64 Image::getHeight()
	{
		return mHeight;
	}

}