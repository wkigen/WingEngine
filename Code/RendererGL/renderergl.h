#ifndef _WING_RENDERERGL_RENDERERGL_H_
#define _WING_RENDERERGL_RENDERERGL_H_

#include "dll\module.h"


#if WING_RENDERERGL_EXPORTS && WING_PLATFORM_WIN32
#define WING_RENDERERGL_API _declspec( dllexport )
#else
#define WING_RENDERERGL_API _declspec(dllimport)
#endif


extern "C"
{

	WING_RENDERERGL_API WingCore::Module* WingDllMain();

}


#endif