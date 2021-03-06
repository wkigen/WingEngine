#ifndef _WING_ENGINE_RESOURCE_H_
#define _WING_ENGINE_RESOURCE_H_

#include "base\object.h"
#include "io\stream.h"
#include "common\engine_defines.h"
#include "common\constant.h"

using namespace WingCore;

#define RESOURCE_TYPE(type)		const static uint32 StaticResourceType = type; 

namespace WingEngine
{

	class WING_ENGINE_API Resource:public Object
	{

	public:

		RESOURCE_TYPE(ResourceTypeNull)

		Resource();
		~Resource();

		virtual uint32 getResourceType() { return mResourceType; }

	protected:
		ResourceType mResourceType;
	};

}


#endif