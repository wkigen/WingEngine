#include "plugin_system.h"
#include "allocator\allocator.h"
#include "log\log.h"

namespace WingEngine
{
	PluginSystem::PluginSystem()
		:mCreate(false)
	{

	}

	PluginSystem::~PluginSystem()
	{

	}

	bool PluginSystem::create()
	{
		if (mCreate)
		{
			WING_LOG_WARN("DllSystem has been create");
			return false;
		}
		mCreate = true;
		return true;
	}

	void PluginSystem::destroy()
	{

	}

	bool PluginSystem::open(const std::string dllPath)
	{
		void* handle = WingCore::dllopen(dllPath.c_str());

		if (handle != nullptr)
		{
			WingDllMain funMain = (WingDllMain)WingCore::dllsym(handle, WING_DLL_MAIN_FUNCTION);
			if (funMain)
			{
				Plugin* plugin = (*funMain)();
				plugin->mHandle = handle;
				mPluginList.push_back(plugin);
				WING_LOG_INFO("Plugin successfully loaded %s", plugin->mName.c_str());
				return true;
			}
		}
		WING_LOG_INFO("Plugin fail loaded %s", dllPath.c_str());
		return false;
	}

	void PluginSystem::close(const std::string name)
	{
		std::list<Plugin*>::iterator iter = mPluginList.begin();
		while (iter != mPluginList.end())
		{
			if ((*iter)->mName.compare(name) == 0)
			{
				WING_LOG_INFO("Plugin successfully unloaded %s", (*iter)->mName.c_str());
				WingCore::dllclose((*iter)->mHandle);
				mPluginList.remove(*iter);
				break;
			}
			iter++;
		}
	}


	std::list<Plugin*> PluginSystem::getPlugin(uint32 type)
	{
		std::list<Plugin*> plugin;
		std::list<Plugin*>::iterator iter = mPluginList.begin();
		while (iter != mPluginList.end())
		{
			if ((*iter)->mType == type)
			{
				plugin.push_back((*iter));
			}
			iter++;
		}
		return plugin;
	}

}