#ifndef _WING_ENGINE_INDEICE_DATA_H_
#define _WING_ENGINE_INDEICE_DATA_H_

#include "base\object.h"
#include "common\defines.h"
#include "common\engine_defines.h"

namespace WingEngine
{

	class WING_ENGINE_API IndeiceData : public WingCore::Object
	{

	public:
		IndeiceData();
		~IndeiceData();

		void* createData(uint64 num);

		void* getData() { return mData; }

		uint64 getDataNum() { return mDataNum; }

		void bindGPUBuffer();

		uint32 getGPUBufferId() { return mGPUBufferId; }
	private:
		//indice struce
		//1(uint32)
		void* mData;
		uint64 mDataNum;
		uint64 mDataSize;
		uint32 mGPUBufferId;
	};


}


#endif // !_WING_ENGINE_INDEICE_DATA_H_