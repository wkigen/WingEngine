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

	}

	void* Image::createData(uint8 bit, ColorType colorType, uint64 width, uint64 height)
	{
		mBit = bit;
		mWidth = width;
		mHeight = height;
		mColorType = colorType;

		uint32 _colorType ;
		switch (colorType)
		{
		case ColorTypeRGB:
			_colorType = 3;
			break;
		case ColorTypeRGBA:
			_colorType = 4;
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

		mData = WING_ALLOC(_bit * width * height * _colorType);
		
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