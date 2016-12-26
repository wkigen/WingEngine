#include "mesh_reader.h"
#include "log\log.h"

namespace WingEngine
{
	bool MeshReader::readResource(Resource* resource)
	{
		if (resource->getResourceType() != ResourceTypeMesh)
		{
			WING_LOG_ERROR("is not the type of mesh");
			return false;
		}

		Mesh* mesh = (Mesh*)resource;



		return true;
	}
}