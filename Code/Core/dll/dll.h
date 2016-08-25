#ifndef _WING_CORE_DLL_H_
#define	_WING_CORE_DLL_H_

#include "common\defines.h"
#include "common\platform.h"

#if WING_PLATFORM_WIN32
#	include <psapi.h>
#endif


namespace WingCore
{
	inline void* dllopen(const char* dllPath)
	{
#if WING_PLATFORM_WIN32
		return (void*)::LoadLibraryA(dllPath);
#endif
	}

	inline void dllclose(void* handle)
	{
#if WING_PLATFORM_WIN32
		::FreeLibrary((HMODULE)handle);
#endif
	}

	inline void* dllsym(void* _handle, const char* _symbol)
	{
#if WING_PLATFORM_WIN32
		return (void*)::GetProcAddress((HMODULE)_handle, _symbol);
#endif
	}
}

#endif