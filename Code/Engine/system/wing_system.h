#ifndef _WING_ENGINE_ENGINE_SYSTEM_H_
#define _WING_ENGINE_ENGINE_SYSTEM_H_

#include "base\singleton.h"
#include "common\defines.h"

namespace WingEngine
{

	class WING_ENGINE_API WingSystem:public WingCore::Singleton<WingSystem>
	{

		friend class WingCore::Singleton<WingSystem>;

	public:
		~WingSystem();

		bool init();
		void destroy();

	private:
		WingSystem();

	private:

	};

}



#endif