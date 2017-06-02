#ifndef _WING_ENGINE_VERTIX_DATA_H_
#define _WING_ENGINE_VERTIX_DATA_H_

#include "base\smart_ptr.h"
#include "base\object.h"
#include "common\defines.h"
#include "common\engine_defines.h"
#include "data_element.h"

namespace WingEngine
{

	class WING_ENGINE_API VertixData : public WingCore::Object
	{
	public:
		VertixData();
		~VertixData();

		void* createData(uint64 num, DataElement* dataElement);

		void* getData() { return mData; }

		uint64 getDataNum() { return mDataNum; }

		uint64 getDataSize() { return mDataSize; }

		DataElement* getElement() { return mDataElement; }

		void bindGPUBuffer();

		uint32 getGPUBufferId() { return mGPUBufferId; }
	private:
		//data struct
		//POSITION       NORMAL         TEXTURE_COORDINATE
		//3(real)        3(real)        2(real)
		void* mData;
		uint64 mDataNum;
		SmartPtr<DataElement> mDataElement;
		uint64 mDataSize;
		uint32 mGPUBufferId;
	};


}


#endif // !_WING_ENGINE_VERTIX_DATA_H_