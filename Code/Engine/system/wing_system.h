#ifndef _WING_ENGINE_ENGINE_SYSTEM_H_
#define _WING_ENGINE_ENGINE_SYSTEM_H_

#include "base\singleton.h"
#include "common\engine_defines.h"
#include "config\config.h"

namespace WingEngine
{

	class WING_ENGINE_API WingSystem:public WingCore::Singleton<WingSystem>
	{

		friend class WingCore::Singleton<WingSystem>;

	public:
		virtual ~WingSystem();

		bool create();
		void destroy();

		void readConfig();
		void setDefaultConfig();

	private:
		WingSystem();

		

	private:
		WingCore::Config mConfig;
	};

}



#endif