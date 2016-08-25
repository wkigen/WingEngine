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
		RendererSystem::getInstance()->create();
	}

	void EngineApplication::destroy()
	{

		WingSystem::getInstance()->destroy();

		WingCore::DllSystem::getInstance()->destroy();
		WingCore::FileSystem::getInstance()->detroy();

		WingCore::Application::destroy();
		RendererSystem::getInstance()->destroy();
	}

	void EngineApplication::run()
	{
		WingCore::Application::run();
	}

}