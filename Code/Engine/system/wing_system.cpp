#include "wing_system.h"
#include "io\file_system.h"
#include "dll\dll_system.h"
#include "log\log.h"

namespace WingEngine
{
	WingSystem::WingSystem()
		:mCreate(false)
	{

	}

	WingSystem::~WingSystem()
	{

	}

	bool WingSystem::create()
	{
		if (mCreate)
		{
			WING_LOG_WARN("DllSystem has been create");
			return false;
		}
		mCreate = true;

		//todo
		WingCore::DllSystem::getInstance()->open("WingRendererGLD.dll");

		return true;
	}

	void WingSystem::destroy()
	{
	}

	void WingSystem::setDefaultConfig()
	{
		mConfig.setAttribute("WingEngine", "version", "0.01");
	}

	void WingSystem::readConfig()
	{

	}

	void WingSystem::run()
	{
		RendererSystem::getInstance()->render();
	}
}