#ifndef _WING_ENGINE_DATA_ELEMENT_H_
#define _WING_ENGINE_DATA_ELEMENT_H_

#include "base\object.h"
#include "common\defines.h"
#include "common\engine_defines.h"
#include "common\constant.h"
namespace WingEngine
{

	class WING_ENGINE_API DataElement : public WingCore::Object
	{

	public:
		DataElement(DataElementType type,uint32 count);
		~DataElement();

		DataElementType getElementType();

		uint32 getCount();

		uint32 getSize();

		uint16 getElementTypeSize();

	private:

		uint32 mSize;
		uint32	mCount;
		DataElementType mElementType;
	};


}


#endif // !_WING_ENGINE_VERTIX_ELEMENT_H_