#ifndef _WING_ENGINE_MESH_H_
#define _WING_ENGINE_MESH_H_

#include "scene\node.h"
#include "resource\resource.h"
#include "common\engine_defines.h"
#include <map>
#include "submesh.h"

namespace WingEngine
{

	class WING_ENGINE_API Mesh:public Node,Resource
	{
	public:
		RESOURCE_TYPE(ResourceTypeMesh)

	public:
		Mesh();
		~Mesh();


	private:
		std::map<std::string, Submesh*> mSubmeshs;
	};

}


#endif