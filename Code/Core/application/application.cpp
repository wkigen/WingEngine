#include "application.h"
#include "allocator\allocator.h"
#ifdef WING_PLATFORM_WIN32
#include "window\windowWindows.h"
#endif

namespace WingCore
{
	Application::Application()
		:mWindow(nullptr)
		, mExit(false)
	{

	}

	Application::~Application()
	{
		
	}

	void Application::create()
	{
#ifdef WING_PLATFORM_WIN32
		mWindow = WING_NEW WindowWindows();
#endif
		mWindow->init();
	}

	void Application::destroy()
	{
		mWindow->destriy();
		WING_DELETE(mWindow);
	}

	void Application::run()
	{
		while (!mExit)
		{

#ifdef WING_PLATFORM_WIN32
			MSG sMsg;
			while (PeekMessage(&sMsg, nullptr, 0, 0, FALSE)) {
				if (sMsg.message == WM_QUIT)
					stop();
				GetMessage(&sMsg, nullptr, 0, 0);
				TranslateMessage(&sMsg);
				DispatchMessage(&sMsg);
			}
#endif
		}
	}

	void Application::stop()
	{
		mExit = true;
	}


}