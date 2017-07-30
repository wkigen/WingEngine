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
		WING_FREE(mData)
	}

	void* VertixData::createData(uint64 num, DataElement* dataElement)
	{
		mDataNum = num;
		mDataElement = dataElement;
		mDataSize = mDataNum * mDataElement->getSize();
		mData = WING_ALLOC(mDataSize);
		return mData;
	}

	void VertixData::bindGPUBuffer()
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		mGPUBufferId = context->bindStaticArrayBuffers(mDataSize, mData);
	}

}