#ifndef _WING_ENGINE_RESOURCE_MESHREADER_H_
#define _WING_ENGINE_RESOURCE_MESHREADER_H_

#include "resource\resource_reader.h"
#include "mesh\mesh.h"

namespace WingEngine
{
	class MeshReader:public ResourceReader
	{

	public:
		MeshReader();
		~MeshReader();

		virtual bool readResource(Resource* resource) { return false; };

	};


}

#endif