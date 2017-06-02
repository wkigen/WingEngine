#ifndef _WING_ENGINE_DATA_ELEMENT_H_
#define _WING_ENGINE_DATA_ELEMENT_H_

#include "base\object.h"
#include "common\defines.h"
#include "common\engine_defines.h"
#include "common\constant.h"
#include <list>

using namespace WingCore;

namespace WingEngine
{
	typedef struct ElementFormat
	{
		DataElementName mDataElentName;
		uint16 mSize;
		uint16 mOffest;
	}ElementFormat;

	class WING_ENGINE_API DataElement : public WingCore::Object
	{

	public:
		DataElement();
		DataElement(DataElementType type,uint32 count);
		~DataElement();

		DataElementType getElementType();

		uint32 getCount();

		uint32 getSize();

		uint16 getElementTypeSize();

		void addElementFromat(DataElementName name,uint16 size,uint16 offest);

		ElementFormat getElementFormat(DataElementName name);
	private:

		uint32 mSize;
		uint32	mCount;
		DataElementType mElementType;
		std::list<ElementFormat> mElementFormats;
	};


}


#endif // !_WING_ENGINE_DATA_ELEMENT_H_