#include "wing_system.h"
#include "io\file_system.h"
#include "plugin\plugin_system.h"
#include "log\log.h"
#include "scene\scene_system.h"

using namespace WingCore;

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
			WING_LOG_WARN("WingSystem has been create");
			return false;
		}
		mCreate = true;

		//todo
		PluginSystem::getInstance()->open("WingRendererGLD.dll");

		return true;
	}

	void WingSystem::destroy()
	{
	}

	void WingSystem::setDefaultConfig()
	{
	
	}

	void WingSystem::readConfig()
	{

	}

	void WingSystem::run()
	{
		Node* cube = SceneSystem::getInstance()->findNode("cube");
		cube->rotate(Vectorf(0, 1, 0),0.001);

		SceneSystem::getInstance()->addNodeToRenderer();
	}
}