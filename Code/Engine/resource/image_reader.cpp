#include "image_reader.h"

namespace WingEngine
{
	ImageReader::ImageReader()
	{

	}

	ImageReader::~ImageReader()
	{

	}

	void ImageReader::pngReadCallback(png_structp png_ptr, png_bytep data, png_size_t length)
	{
		PngData* pSourceData = (PngData*)png_get_io_ptr(png_ptr);// ��png_ptr����������ṹ��  

		if ((int)(pSourceData->offset + length) <= pSourceData->size)
		{
			memcpy(data, pSourceData->data + pSourceData->offset, length);
			pSourceData->offset += length;
		}
		else
		{
			png_error(png_ptr, "PngReaderCallback failed.\n");
		}
	}

	bool ImageReader::readResource(Resource* resource)
	{
		Image* image = (Image*)resource;

		if (image == nullptr || image->getResourceType() != ResourceTypeImage)
		{
			WING_LOG_ERROR("is not the type of mesh");
			return false;
		}

		png_structp png_ptr;
		png_infop info_ptr;

		// ��ʼ��libpng, �쳣������ʹ��Ĭ�ϵ�  
		png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
		// ����ͼ����Ϣ��������ͼ�����ݽ�����������  
		info_ptr = png_create_info_struct(png_ptr);
		if (info_ptr == NULL)
		{
			png_destroy_read_struct(&png_ptr, NULL, NULL);
			return false;
		}
		// �����쳣���󷵻ص㣻��ʼ��libpng��ʱ��δָ���û��Զ���Ĵ�����������£�����Ҫ����  
		if (setjmp(png_jmpbuf(png_ptr)))
		{
			png_destroy_read_struct(&png_ptr, (info_ptr) ? &info_ptr : 0, 0);
			return false;
		}

		uint64 fileSize = mStream->getSize();
		uint8* data = (uint8*)WING_ALLOC(fileSize);
		mStream->read(data, fileSize);

		PngData pngData;
		pngData.data = (uint8*)data;
		pngData.offset = 0;
		pngData.size = fileSize;
		png_set_read_fn(png_ptr, (void *)&pngData, pngReadCallback);

		// ��ȡPNG�ļ���Ϣ�����ûص������������ݵ�info_ptr��  
		png_read_info(png_ptr, info_ptr);

		uint64 width = png_get_image_width(png_ptr, info_ptr);
		uint64 height = png_get_image_height(png_ptr, info_ptr);
		uint8 bitsComponent = png_get_bit_depth(png_ptr, info_ptr);

		// ��С��ת��  
		if (bitsComponent > 8)
		{
			png_set_swap(png_ptr);
		}

		uint32 colorType = png_get_color_type(png_ptr, info_ptr);

		if (colorType == PNG_COLOR_TYPE_PALETTE)
		{
			png_set_palette_to_rgb(png_ptr);
		}
		if (colorType == PNG_COLOR_TYPE_GRAY && bitsComponent < 8)
		{
			png_set_expand_gray_1_2_4_to_8(png_ptr);
		}
		if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
		{
			png_set_tRNS_to_alpha(png_ptr);
		}
		if (bitsComponent == 16)
		{
			png_set_strip_16(png_ptr);
		}
		if (colorType == PNG_COLOR_TYPE_GRAY || colorType == PNG_COLOR_TYPE_GRAY_ALPHA)
		{
			png_set_gray_to_rgb(png_ptr);
		}

		bitsComponent = 8;

		png_read_update_info(png_ptr, info_ptr);

		png_bytep imageData;
		switch (colorType)
		{
		case PNG_COLOR_TYPE_RGB_ALPHA:
			imageData = (png_bytep)image->createData(bitsComponent, ColorTypeRGBA, width, height);
			break;
		case PNG_COLOR_TYPE_RGB:
			imageData = (png_bytep)image->createData(bitsComponent, ColorTypeRGBA, width, height);
			break;
		default:
			WING_LOG_ERROR("can not read png without rgba & rgb");
			png_destroy_read_struct(&png_ptr, &info_ptr, 0);
			return false;
			break;
		}

		if (imageData == nullptr)
		{
			return false;
		}

		png_uint_32 rowbytes = png_get_rowbytes(png_ptr, info_ptr);
		png_bytepp row_pointers = new png_bytep[height];
		for (uint32 i = 0; i <height; ++i)
		{
			row_pointers[i] = (imageData + i * rowbytes);
		}
		png_read_image(png_ptr,row_pointers);

		// ����ͼƬ����  
		png_read_end(png_ptr, NULL);
		if (png_ptr)
		{
			png_destroy_read_struct(&png_ptr, (info_ptr) ? &info_ptr : 0, 0);
		}

		WING_FREE(data);

		return true;
	}


}