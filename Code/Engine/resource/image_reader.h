#ifndef _WING_ENGINE_RESOURCE_IMAGE_READER_H_
#define _WING_ENGINE_RESOURCE_IMAGE_READER_H_

#include "resource\resource_reader.h"
#include "image.h"
#include "log\log.h"
#include "LibPNG\png.h"

#define PNG_BYTES_TO_CHECK 4  

typedef struct
{
	png_byte* data;
	int32 size;
	int32 offset;

}PngData;

namespace WingEngine
{
	class ImageReader:public ResourceReader
	{

	public:
		ImageReader();
		~ImageReader();

		virtual bool readResource(Resource* resource);

	private:
		static void pngReadCallback(png_structp png_ptr, png_bytep data, png_size_t length);
	};

}

#endif