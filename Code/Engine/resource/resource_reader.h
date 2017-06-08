#ifndef _WING_ENGINE_RESOURCE_READER_H_
#define _WING_ENGINE_RESOURCE_READER_H_

#include "common\constant.h"
#include "io\reader.h"
#include "resource\resource.h"

namespace WingEngine
{

	class ResourceReader:public Reader
	{
	public:
		ResourceReader();
		~ResourceReader();

		template<class T>
		bool readResource(T* resource) = 0;
	};

}

#endif