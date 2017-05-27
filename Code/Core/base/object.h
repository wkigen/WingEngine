#ifndef _WING_CORE_OBJECT_H_
#define _WING_CORE_OBJECT_H_

#include "common\defines.h"

namespace WingCore
{

	class WING_CORE_API Object
	{

	public:

		Object();
		virtual ~Object();

		virtual uint32	addReference();

		virtual uint32	release();

		virtual uint32	getRefCount();

	private:
		uint32	mRefCount;

	};

}

#endif