#ifndef _WING_ENGINE_VERTIX_DATA_H_
#define _WING_ENGINE_VERTIX_DATA_H_

#include "base\object.h"
#include "common\defines.h"
#include "common\engine_defines.h"

namespace WingEngine
{

	class WING_ENGINE_API VertixData : public WingCore::Object
	{
	public:
		VertixData();
		~VertixData();

		void* createData(uint64 num);

		void* getData() { return mData; }

		uint64 getDataNum() { return mDataNum; }

		uint64 getDataSize() { return mDataSize; }

		uint64 getElementSize() { return mElementSize; }

		void bindGPUBuffer();

		uint32 getGPUBufferId() { return mGPUBufferId; }
	private:
		//data struct
		//POSITION       NORMAL         TEXTURE_COORDINATE
		//3(real)        3(real)        2(real)
		void* mData;
		uint64 mDataNum;
		uint32 mElementSize;
		uint64 mDataSize;
		uint32 mGPUBufferId;
	};


}


#endif // !_WING_ENGINE_VERTIX_DATA_H_