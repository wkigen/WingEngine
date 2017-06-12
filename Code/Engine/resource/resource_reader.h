#ifndef _WING_ENGINE_RESOURCE_READER_H_
#define _WING_ENGINE_RESOURCE_READER_H_

#include "allocator\allocator.h"
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

		virtual bool readResource(Resource* resource) { return false; };

	};

}

#endif