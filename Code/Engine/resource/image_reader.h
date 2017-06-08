#ifndef _WING_ENGINE_RESOURCE_IMAGE_READER_H_
#define _WING_ENGINE_RESOURCE_IMAGE_READER_H_

#include "resource\resource_reader.h"
#include "image.h"
#include "log\log.h"


namespace WingEngine
{
	class ImageReader:public ResourceReader
	{

	public:
		ImageReader();
		~ImageReader();

		template<class T>
		 bool readResource(T* resource);

	};


	template<class T>
	 bool ImageReader::readResource(T* resource)
	{
		if (T->getResourceType() != ResourceTypeImage)
		{
			WING_LOG_ERROR("is not the type of mesh");
			return false;
		}

		Image* image = (Image*)resource;



		return true;
	}

}

#endif