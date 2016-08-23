
#ifndef _WING_CORE_DEFINES_H_
#define _WING_CORE_DEFINES_H_

#include <stdint.h>

#if WING_CORE_EXPORTS && WING_PLATFORM_WIN32
#define WING_CORE_API _declspec( dllexport )
#else
#define WING_CORE_API _declspec(dllimport)
#endif

typedef unsigned char	uint8;
typedef char			int8;
typedef unsigned short	uint16;
typedef short			int16;
typedef unsigned int	uint32;
typedef int				int32;
typedef unsigned long	uint64;
typedef long			int64;
#if WING_DOUBLE
typedef double			real;
#else
typedef float			real;
#endif


#define INT8MAX         127i8
#define INT16MAX        32767i16
#define INT32MAX        2147483647i32
#define INT64MAX        9223372036854775807i64
#define UINT8MAX        0xffui8
#define UINT16MAX       0xffffui16
#define UINT32MAX       0xffffffffui32
#define UINT64MAX       0xffffffffffffffffui64

#define NULL			0

#endif