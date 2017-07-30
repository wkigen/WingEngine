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
		WING_FREE(mData)
	}

	void* IndeiceData::createData(uint64 num, DataElement* dataElement)
	{
		mDataNum = num;
		mDataElement = dataElement;
		mDataSize = mDataNum * mDataElement->getSize();
		mData = WING_ALLOC(mDataSize);
		return mData;
	}

	void IndeiceData::bindGPUBuffer()
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		mGPUBufferId = context->bindElementBuffers(mDataSize, mData);
	}

}