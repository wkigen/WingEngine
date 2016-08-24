#ifndef _WING_CORE_RESOURCE_READER_H_
#define _WING_CORE_RESOURCE_READER_H_

#include "reader.h"
#include "resource\resource.h"

namespace WingCore
{
	class WING_CORE_API ResourceReader:public Reader
	{
	public:
		virtual bool readResource(Resource* resource)=0;
	};

}

#endif