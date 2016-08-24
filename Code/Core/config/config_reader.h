#ifndef _WING_CONGIF_READER_H_
#define _WING_CONGIF_READER_H_

#include "config.h"
#include "io\resource_reader.h"

namespace WingCore
{
	class WING_CORE_API ConfigReader:public ResourceReader
	{
	public:
		virtual bool readResource(Resource* resource);
	};
}

#endif