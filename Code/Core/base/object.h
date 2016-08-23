#ifndef _WING_CORE_OBJECT_H_
#define _WING_CORE_OBJECT_H_

#include "common\defines.h"

namespace WingCore
{

	class WING_CORE_API Object
	{

	public:
		Object():mRefCount(0){};
		~Object() {};

		inline uint32	addReference() { mRefCount++; return mRefCount; }

		inline uint32	release() { mRefCount--; return mRefCount; }

		inline uint32	getRefCount() { return mRefCount; }

	private:
		uint32	mRefCount;

	};

}

#endif