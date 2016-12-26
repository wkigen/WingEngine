#include "scene_system.h"
#include "io\file_system.h"
#include "dll\dll_system.h"
#include "log\log.h"

namespace WingEngine
{
	SceneSystem::SceneSystem()
		:mCreate(false)
	{

	}

	SceneSystem::~SceneSystem()
	{

	}

	bool SceneSystem::create()
	{
		if (mCreate)
		{
			WING_LOG_WARN("SceneSystem has been create");
			return false;
		}
		mCreate = true;

		mRootNode = new Node();
		mRootNode->setName(ROOTNODE);

		return true;
	}

	void SceneSystem::destroy()
	{
	}

}