#ifndef _WING_CORE_RESOURCE_H_
#define _WING_CORE_RESOURCE_H_

namespace WingCore
{
	struct ResourceType
	{
		enum Enum
		{
			CONFIG,

			COUNT,
		};
	};

#define RESOURCE_TYPE(type)		const static ResourceType::Enum mType = type;

	class Resource
	{
		RESOURCE_TYPE(ResourceType::COUNT)
	public:

		static inline ResourceType::Enum getResourceType() { return mType; }

	private:
		
	};

}


#endif