#ifndef _WING_ENGINE_RESOURCE_READER_H_
#define _WING_ENGINE_RESOURCE_READER_H_

#include "io\reader.h"
#include "resource\resource.h"

namespace WingEngine
{

	class ResourceReader:public Reader
	{
	public:
		ResourceReader();
		~ResourceReader();

		virtual bool readResource(Resource* resource) = 0;
	};

}

#endif