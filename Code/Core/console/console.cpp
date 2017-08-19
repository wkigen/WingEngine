#include "console.h"
#include <stdio.h>
namespace WingCore
{
	void Console::open()
	{
#if WING_PLATFORM_WIN32
		AllocConsole();
		freopen("conout$", "w", stdout);
#endif // WING_PLATFORM_WIN32
	}


	void Console::close()
	{
#if WING_PLATFORM_WIN32
		fclose(stdout);
		FreeConsole();
#endif // WING_PLATFORM_WIN32
	}



}