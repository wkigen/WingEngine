#ifndef _WING_CORE_PLATFORM_H_
#define _WING_CORE_PLATFORM_H_


#if WING_PLATFORM_WIN32
#include <windows.h>
#endif

#if defined(_MSC_VER)
#	define WING_CORE_MSVC_MSC_VER
#endif



#endif