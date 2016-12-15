#include "engine_application.h"
#include "io\file_system.h"
#include "dll\dll_system.h"
#include "system\wing_system.h"

namespace WingEngine
{
	EngineApplication::EngineApplication()
	{

	}

	EngineApplication::~EngineApplication()
	{

	}

	void EngineApplication::create()
	{
		WingCore::Application::create();

		WingCore::FileSystem::getInstance()->create();
		WingCore::DllSystem::getInstance()->create();

		WingSystem::getInstance()->create();
		RendererSystem::getInstance()->create(mWindow->getHandle(),mWindow->getWidth(),mWindow->getHeight());
	}

	void EngineApplication::destroy()
	{
		RendererSystem::getInstance()->destroy();
		WingSystem::getInstance()->destroy();

		WingCore::DllSystem::getInstance()->destroy();
		WingCore::FileSystem::getInstance()->detroy();


		WingCore::Application::destroy();
	}

	void EngineApplication::run()
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
			WingSystem::getInstance()->run();

			RendererSystem::getInstance()->render();

			
		}

		
	}

}