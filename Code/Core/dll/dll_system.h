#ifndef _WING_CORE_DLL_SYSTEM_H_
#define _WING_CORE_DLL_SYSTEM_H_

#include "dll.h"
#include "module.h"
#include "base\singleton.h"
#include <list>

namespace WingCore
{

#define WING_DLL_MAIN_FUNCTION	"WingDllMain"

typedef Module*				(*WingDllMain) ();

	class WING_API DllSystem:public Singleton<DllSystem>
	{

		friend class Singleton<DllSystem>;


	public:
		bool	open(const std::string dllPath);
		void	close(const std::string name);

	private:

		std::list<Module*>		mDllList;
	};


}


#endif