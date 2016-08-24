#ifndef _WING_ENGINE_APPLICATION_H_
#define _WING_ENGINE_APPLICATION_H_

#include "common\engine_defines.h"
#include "application\application.h"

namespace WingEngine
{

	class WING_ENGINE_API EngineApplication:public WingCore::Application
	{

	public:
		EngineApplication();
		virtual ~EngineApplication();

		virtual void create();
		virtual void destroy();

		virtual bool init() = 0;
		virtual void clear() = 0;

		virtual void run();

	private:

	};

}


#endif