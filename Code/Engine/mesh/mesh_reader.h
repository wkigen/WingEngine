#ifndef _WING_ENGINE_RESOURCE_MESHREADER_H_
#define _WING_ENGINE_RESOURCE_MESHREADER_H_

#include "resource\resource_reader.h"
#include "mesh\mesh.h"

namespace WingEngine
{
	class WING_CORE_API MeshReader:public ResourceReader
	{

	public:
		virtual bool readResource(Resource* resource);

	};

}

#endif