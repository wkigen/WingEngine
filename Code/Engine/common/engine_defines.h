#ifndef _WING_ENGINE_DEFINES_H_
#define _WING_ENGINE_DEFINES_H_

#include <stdint.h>

#if WING_ENGINE_EXPORTS && WING_PLATFORM_WIN32
#define WING_ENGINE_API _declspec( dllexport )
#else
#define WING_ENGINE_API _declspec(dllimport)
#endif

#endif