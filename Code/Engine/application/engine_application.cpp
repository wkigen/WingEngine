#include "engine_application.h"
#include "io\file_system.h"
#include "plugin\plugin_system.h"
#include "system\wing_system.h"
#include "resource\resource_system.h"
#include "font\font_system.h"

using namespace WingCore;

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
		Application::create();

		WingSystem::getInstance()->create();

		FileSystem::getInstance()->create();

		PluginSystem::getInstance()->create();

		ResourceSystem::getInstance()->create();

		FontSystem::getInstance()->create();

		RendererSystem::getInstance()->create(mWindow->getHandle(),mWindow->getWidth(),mWindow->getHeight());
	}

	void EngineApplication::destroy()
	{
		RendererSystem::getInstance()->destroy();

		FontSystem::getInstance()->destroy();

		ResourceSystem::getInstance()->destroy();
	
		PluginSystem::getInstance()->destroy();

		FileSystem::getInstance()->detroy();

		WingSystem::getInstance()->destroy();

		Application::destroy();

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
			frame();

			WingSystem::getInstance()->run();

			RendererSystem::getInstance()->render();

		}
		
	}

	void EngineApplication::adjust(uint32 _width, uint32 _height)
	{

	}

}