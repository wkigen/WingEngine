#include "data_element.h"
#include "allocator\allocator.h"
#include "renderer_system.h"

namespace WingEngine
{

	DataElement::DataElement(DataElementType type, uint32 count)
		:mElementType(type)
		,mCount(count)
	{
		mSize = getElementTypeSize() * count;
	}

	DataElement::~DataElement()
	{

	}


	DataElementType VertixElement::getElementType()
	{
		return mElementType;
	}

	uint32 VertixElement::getCount()
	{
		return mCount;
	}

	uint32 VertixElement::getSize()
	{
		return mSize;
	}


	uint16 VertixElement::getElementTypeSize()
	{
		switch (mElementType) {
		case DataElementType::UBYTE:
		case DataElementType::BYTE:
			return 1;
		case DataElementType::USHORT:
		case DataElementType::SHORT:
			return 2;
		case DataElementType::UINT:
		case DataElementType::INT:
			return 4;
		case DataElementType::ULONG:
		case DataElementType::LONG:
			return 8;
		case DataElementType::REAL:
			return 4;
		default:
			return 0;
		}
	}
	
}