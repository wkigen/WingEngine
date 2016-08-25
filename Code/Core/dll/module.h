#ifndef _WING_CORE_MODULE_H_
#define _WING_CORE_MODULE_H_

#include <string>
#include "common\defines.h"

namespace WingCore
{
#define ModuleTypeNull	0

	struct Module
	{
		Module()
			:mHandle(nullptr)
			,mObject(nullptr)
			,mType(ModuleTypeNull)
			,mName("")
		{

		}

		void*				mHandle;
		void*				mObject;
		uint32				mType;
		std::string			mName;
	};
}

#endif