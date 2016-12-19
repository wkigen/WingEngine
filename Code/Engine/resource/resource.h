#ifndef _WING_ENGINE_RESOURCE_H_
#define _WING_ENGINE_RESOURCE_H_

#include "io\stream.h"
#include "common\engine_defines.h"

using namespace WingCore;

namespace WingEngine
{

#define ResourceTypeNull	0
#define ResourceTypeConfig	1
#define ResourceTypeMesh	2
#define ResourceTypeMax		30

#define RESOURCE_TYPE(type)		const static uint32 mType = type; \
								static inline uint32 getResourceType() { return mType; }

	class WING_ENGINE_API Resource
	{

	public:
		RESOURCE_TYPE(ResourceTypeNull)

	public:

		virtual void read(Stream* stream) = 0;
		virtual void write(Stream* stream) = 0;
	private:
		
	};

}


#endif