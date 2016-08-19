#ifndef _WING_CORE_ERROR_H_
#define _WING_CORE_ERROR_H_

#include "common\defines.h"
#include "log\log.h"
#include <assert.h>


#define WING_ASSERT(flag)	assert(flag)

#define WING_FATE(flag,info)	do{	\
									if(!flag)	{	\
										WING_LOG_ERROR(info);	\
									}	\
								}while(0)	\

#endif