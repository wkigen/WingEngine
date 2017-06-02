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

	}

	void* VertixData::createData(uint64 num)
	{
		mDataNum = num;
		mElementSize = sizeof(real) *( 3 + 3 + 2);
		mDataSize = mDataNum * mElementSize;
		mData = WING_ALLOC(mDataSize);
		return mData;
	}

	void VertixData::bindGPUBuffer()
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		mGPUBufferId = context->bindStaticArrayBuffers(mDataSize, mData);
	}

}