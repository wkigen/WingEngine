#ifndef _WING_ENGINE_RESOURCE_WRITER_H_
#define _WING_ENGINE_RESOURCE_WRITER_H_

#include "io\writer.h"
#include "resource\resource.h"

namespace WingEngine
{
	class WING_CORE_API ResourceWriter:public Writer
	{
	public:
		virtual bool writerResource(Resource* resource)=0;
	};

}

#endif