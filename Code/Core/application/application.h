#ifndef _WING_CORE_APPLICATION_H_
#define _WING_CORE_APPLICATION_H_

#include "main.h"
#include "window\window.h"

namespace WingCore
{
	class WING_CORE_API Application
	{
	public:
		Application();
		virtual ~Application();

		virtual void create();
		virtual void destroy();

		virtual bool init()=0;
		virtual void clear()=0;
		
		virtual void run()=0;
		virtual void frame()=0;
		virtual void stop();

	protected:
		bool	mExit;
		Window* mWindow;

	};
}

#endif