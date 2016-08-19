#ifndef _WING_CORE_MODULE_H_
#define _WING_CORE_MODULE_H_

#include <string>
#include "common\defines.h"

namespace WingCore
{
	struct ModuleType
	{
		enum Enum
		{
			RENDERER,

			COUNT,
		};
	};

	struct Module
	{
		Module()
			:mHandle(nullptr)
			,mObject(nullptr)
			,mType(ModuleType::COUNT)
			,mName("")
		{

		}

		void*				mHandle;
		void*				mObject;
		ModuleType::Enum	mType;
		std::string			mName;
	};
}

#endif