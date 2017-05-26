#include "vertix_data.h"
#include "allocator\allocator.h"


namespace WingEngine
{

	VertixData::VertixData()
	{

	}

	VertixData::~VertixData()
	{
		WING_FREE(mData);
	}

	void* VertixData::createData(uint64 num)
	{
		mDataNum = num;
		mData = WING_ALLOC(sizeof(real)*mDataNum * 3 * 3 * 2);
		return mData;
	}



}