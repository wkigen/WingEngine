#ifndef _WING_CONGIF_GROUP_STREAM_H_
#define _WING_CONGIF_GROUP_STREAM_H_

#include <string>
#include <map>
#include <vector>
#include "allocator\allocator.h"
#include "common\defines.h"

namespace WingCore
{
	struct ConfigAttributeType
	{
		enum Enum
		{
			STRING,
			NUMERIC,
			COUNT,
		};
	};

	typedef struct WING_API ConfigAttribute
	{
		ConfigAttribute()
			:mName("")
			,mObject("")
			,mType(ConfigAttributeType::COUNT)
		{

		}
		std::string					mName;
		std::string					mObject;
		ConfigAttributeType::Enum	mType;

	}ConfigGroupAttribute;


	typedef struct WING_API ConfigGroup
	{
		ConfigGroup()
			:mName("")
		{
		}
		std::string						mName;
		std::vector<ConfigAttribute>	mAttrubute;

	}ConfigGroup;

	typedef std::vector<ConfigAttribute>		ConfigAttributes;
	typedef std::map<std::string, ConfigGroup>	ConfigCroups;

}

#endif