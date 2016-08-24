#ifndef _WING_CORE_RESOURCE_WRITER_H_
#define _WING_CORE_RESOURCE_WRITER_H_

#include "writer.h"
#include "resource\resource.h"

namespace WingCore
{
	class WING_CORE_API ResourceWriter:public Writer
	{
	public:
		virtual bool writerResource(Resource* resource)=0;
	};

}

#endif