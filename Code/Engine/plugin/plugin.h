#ifndef _WING_ENGINE_PLUGIN_H_
#define _WING_ENGINE_PLUGIN_H_

#include <string>
#include "common\defines.h"
#include "common\constant.h"

namespace WingEngine
{


	struct Plugin
	{
		Plugin()
			:mHandle(nullptr)
			,mObject(nullptr)
			,mType(PluginTypeNull)
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