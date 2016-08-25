#ifndef _WING_CORE_RESOURCE_H_
#define _WING_CORE_RESOURCE_H_

namespace WingCore
{

#define ResourceTypeNull	0
#define RespirceTypeConfig	1
#define ResourceTypeMax		30

#define RESOURCE_TYPE(type)		const static uint32 mType = type;

	class Resource
	{
		RESOURCE_TYPE(ResourceTypeNull)
	public:

		static inline uint32 getResourceType() { return mType; }

	private:
		
	};

}


#endif