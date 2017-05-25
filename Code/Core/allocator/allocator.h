#ifndef _WING_CORE_ALLOCATOR_H_
#define _WING_CORE_ALLOCATOR_H_

#include <memory>
#include "common\defines.h"

#define WING_ALLOC(size)		::malloc(size)
#define WING_FREE(ptr)			if(ptr) { ::free(ptr); }

#define WING_NEW				new
#define WING_DELETE(ptr)		if(ptr) { delete ptr; ptr = nullptr;}

#endif