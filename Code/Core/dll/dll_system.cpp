#include "dll_system.h"
#include "allocator\allocator.h"
#include "log\log.h"

namespace WingCore
{

	bool DllSystem::open(const std::string dllPath)
	{
		void* handle = WingCore::dllopen(dllPath.c_str());

		if (handle != nullptr)
		{
			WingDllMain funMain = (WingDllMain)dllsym(handle, WING_DLL_MAIN_FUNCTION);
			if (funMain)
			{
				Module* module = (*funMain)();
				module->mHandle = handle;
				mDllList.push_back(module);
				WING_LOG_INFO("Plugin successfully loaded %s", module->mName.c_str());
				return true;
			}
		}

		return false;
	}

	void DllSystem::close(const std::string name)
	{
		std::list<Module*>::iterator iter = mDllList.begin();
		while (iter != mDllList.end())
		{
			if ((*iter)->mName.compare(name) == 0)
			{
				WING_LOG_INFO("Plugin successfully unloaded %s", (*iter)->mName.c_str());
				dllclose((*iter)->mHandle);
				mDllList.remove(*iter);
				break;
			}
			iter++;
		}
	}

}