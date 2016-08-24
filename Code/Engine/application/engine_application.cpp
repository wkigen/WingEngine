#include "engine_application.h"
#include "io\file_system.h"
#include "dll\dll_system.h"

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

	}

	void EngineApplication::destroy()
	{


		WingCore::DllSystem::getInstance()->destroy();
		WingCore::FileSystem::getInstance()->detroy();
		WingCore::Application::destroy();
	}


	void EngineApplication::run()
	{
		WingCore::Application::run();
	}

}