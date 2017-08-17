#ifndef _WING_CORE_ALLOCATOR_H_
#define _WING_CORE_ALLOCATOR_H_

#include <memory>
#include "common\defines.h"

#define WING_ALLOC(size)		::malloc(size)
#define WING_FREE(ptr)			if(ptr) { ::free(ptr); }

#if  WING_DEBUG && WING_PLATFORM_WIN32
#define WING_NEW				new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define WING_NEW				new
#endif //  WING_DEBUG

#define WING_DELETE(ptr)		if(ptr) { delete ptr; ptr = nullptr;}

#endif