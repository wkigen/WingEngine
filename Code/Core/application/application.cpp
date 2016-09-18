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

	void Application::stop()
	{
		mExit = true;
	}
}