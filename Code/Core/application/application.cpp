#include "application.h"
#include "allocator\allocator.h"
#ifdef WING_PLATFORM_WIN32
#include "window\windowWindows.h"
#endif
#include "console\console.h"

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
#if WING_DEBUG
		Console::open();
#endif

#ifdef WING_PLATFORM_WIN32
		mWindow = WING_NEW WindowWindows();
#endif
		mWindow->init();


	}

	void Application::destroy()
	{
		mWindow->destriy();
		WING_DELETE(mWindow);

#if WING_DEBUG
		Console::close();
#endif
	}

	void Application::stop()
	{
		mExit = true;
	}
}