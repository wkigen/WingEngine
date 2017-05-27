#include "vertix_data.h"
#include "allocator\allocator.h"
#include "renderer_system.h"

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
		mDataSize = sizeof(real)*mDataNum * 3 * 3 * 2;
		mData = WING_ALLOC(mDataSize);
		return mData;
	}

	void VertixData::bindGPUBuffer()
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		mGPUBufferId = context->bindStaticArrayBuffers(mDataSize, mData);
	}

}