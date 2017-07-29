#ifndef _WING_ENGINE_PLUGIN_SYSTEM_H_
#define _WING_ENGINE_PLUGIN_SYSTEM_H_

#include "dll\dll.h"
#include "plugin.h"
#include "base\singleton.h"
#include "common\engine_defines.h"
#include <list>

using namespace WingCore;

namespace WingEngine
{

#define WING_DLL_MAIN_FUNCTION	"WingDllMain"

typedef Plugin*				(*WingDllMain) ();

	class WING_ENGINE_API PluginSystem:public Singleton<PluginSystem>
	{

		friend class Singleton<PluginSystem>;

	public:
		
		virtual ~PluginSystem();

		bool	create();
		void	destroy();

		bool	open(const std::string dllPath);
		void	close(const std::string name);

		std::list<Plugin*>	getPlugin(uint32 type);

	private:
		PluginSystem();

	protected:
		std::list<Plugin*>		mPluginList;

	private:
		bool					mCreate;
		
	};


}


#endif