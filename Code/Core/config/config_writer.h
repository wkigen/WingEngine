#ifndef _WING_CONGIF_WRITER_H_
#define _WING_CONGIF_WRITER_H_

#include "config.h"
#include "io\resource_writer.h"

namespace WingCore
{
	class WING_CORE_API ConfigWriter:public ResourceWriter
	{
	public:
		virtual bool writerResource(Resource* resource);
	};
}

#endif