#ifndef _WING_ENGINE_RESOURCE_WRITER_H_
#define _WING_ENGINE_RESOURCE_WRITER_H_

#include "io\writer.h"
#include "resource\resource.h"

namespace WingEngine
{
	class ResourceWriter:public Writer
	{
	public:
		ResourceWriter();
		~ResourceWriter();

		virtual bool writerResource(Resource* resource)=0;
	};

}

#endif