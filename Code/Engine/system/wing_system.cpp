#include "wing_system.h"
#include "io\file_system.h"

namespace WingEngine
{
	WingSystem::WingSystem()
	{

	}

	WingSystem::~WingSystem()
	{

	}

	bool WingSystem::create()
	{

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
}