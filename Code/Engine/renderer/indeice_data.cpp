#include "indeice_data.h"
#include "allocator\allocator.h"


namespace WingEngine
{

	IndeiceData::IndeiceData()
	{

	}

	IndeiceData::~IndeiceData()
	{
		WING_FREE(mData);
	}

	void* IndeiceData::createData(uint64 num)
	{
		mDataNum = num;
		mData = WING_ALLOC(sizeof(real)*mDataNum * 3 * 3 * 2);
		return mData;
	}


}