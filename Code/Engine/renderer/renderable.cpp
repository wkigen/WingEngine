#include "renderable.h"
#include "allocator\allocator.h"

using namespace WingCore;

namespace WingEngine
{

	Renderable::Renderable()
	{

	}

	Renderable::~Renderable()
	{
		WING_FREE(mData);
		WING_FREE(mIndeice);
	}


	real* Renderable::createData(uint64 size)
	{
		mData = (real*)WING_ALLOC(sizeof(real)*size*3*3*2);
		return mData;
	}

	uint32* Renderable::createIndeice(uint64 size)
	{
		mIndeice = (uint32*)WING_ALLOC(sizeof(uint32)*size);
		return mIndeice;
	}



}