#include "renderer_system.h"
#include "log\log.h"
#include "dll\dll_system.h"
#include "common\constant.h"

namespace WingEngine
{
	RendererSystem::RendererSystem()
		:mCreate(false)
	{

	}

	RendererSystem::~RendererSystem()
	{

	}

	bool RendererSystem::create()
	{
		if (mCreate)
		{
			WING_LOG_WARN("DllSystem has been create");
			return false;
		}
		mCreate = true;


		std::list<WingCore::Module*> rendererDll = WingCore::DllSystem::getInstance()->getMoudles(ModuleTypeRenderer);
		std::list<WingCore::Module*>::iterator iter = rendererDll.begin();
		while (iter != rendererDll.end())
		{
			RendererContext* context = (RendererContext*)(*iter)->mObject;
			if (context)
				mRendererContexts[(*iter)->mName] = context;
			iter++;
		}

		return true;
	}

	void RendererSystem::destroy()
	{

	}
}