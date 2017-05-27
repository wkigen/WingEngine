#include "object.h"

namespace WingCore
{

	Object::Object() 
		:mRefCount(0) 
	{
	};

	Object::~Object() 
	{

	};

	uint32	Object::addReference() 
	{ 
		mRefCount++; return mRefCount; 
	}

	uint32	Object::release() 
	{
		mRefCount--;
		return mRefCount; 
	}

	uint32	Object::Object::getRefCount() 
	{
		return mRefCount; 
	}
}