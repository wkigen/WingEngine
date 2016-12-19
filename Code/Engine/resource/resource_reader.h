#ifndef _WING_ENGINE_RESOURCE_READER_H_
#define _WING_ENGINE_RESOURCE_READER_H_

#include "io\reader.h"
#include "resource\resource.h"

namespace WingEngine
{
	class WING_CORE_API ResourceReader:public Reader
	{
	public:
		virtual bool readResource(Resource* resource)=0;
	};

}

#endif