#include "indeice_data.h"
#include "allocator\allocator.h"
#include "renderer_system.h"

namespace WingEngine
{

	IndeiceData::IndeiceData()
	{

	}

	IndeiceData::~IndeiceData()
	{
	}

	void* IndeiceData::createData(uint64 num)
	{
		mDataNum = num;
		mElementSize = 1;
		mDataSize = sizeof(uint32)*mDataNum * mElementSize;
		mData = WING_ALLOC(mDataSize);
		return mData;
	}

	void IndeiceData::bindGPUBuffer()
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		mGPUBufferId = context->bindElementBuffers(mDataSize, mData);
	}

}