#include "data_element.h"
#include "allocator\allocator.h"
#include "renderer_system.h"

namespace WingEngine
{
	DataElement::DataElement()
		:mElementType(DataElementType::DataElementInt)
		, mCount(1)
	{

	}

	DataElement::DataElement(DataElementType type, uint32 count)
		:mElementType(type)
		,mCount(count)
	{
		mSize = getElementTypeSize() * count;
	}

	DataElement::~DataElement()
	{

	}


	DataElementType DataElement::getElementType()
	{
		return mElementType;
	}

	uint32 DataElement::getCount()
	{
		return mCount;
	}

	uint32 DataElement::getSize()
	{
		return mSize;
	}


	uint16 DataElement::getElementTypeSize()
	{
		switch (mElementType) {
		case DataElementType::DataElementUByte:
		case DataElementType::DataElementByte:
			return 1;
		case DataElementType::DataElementUShort:
		case DataElementType::DataElementShort:
			return 2;
		case DataElementType::DataElementUInt:
		case DataElementType::DataElementInt:
			return 4;
		case DataElementType::DataElementULong:
		case DataElementType::DataElementLong:
			return 8;
		case DataElementType::DataElementReal:
			return 4;
		default:
			return 0;
		}
	}


	void DataElement::addElementFromat(DataElementName name, uint16 size, uint16 offest)
	{
		ElementFormat format;
		format.mDataElentName = name;
		format.mSize = size;
		format.mOffest = offest;
		mElementFormats.push_back(format);
	}

	ElementFormat DataElement::getElementFormat(DataElementName name)
	{
		std::list<ElementFormat>::iterator beg = mElementFormats.begin();
		for(; beg != mElementFormats.end(); beg++)
		{
			if (beg->mDataElentName == name)
			{
				return *beg;
			}
		}
	}
	
}