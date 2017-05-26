#include "scene_system.h"
#include "io\file_system.h"
#include "dll\dll_system.h"
#include "log\log.h"
#include "allocator\allocator.h"

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

		mRootNode = WING_NEW Node();
		mRootNode->setName(ROOTNODE);

		return true;
	}

	void SceneSystem::destroy()
	{
	}

}