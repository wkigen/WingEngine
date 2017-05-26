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

		virtual void* createData(uint64 num);

		virtual void* getData() { return mData; }

		virtual uint64 getDataNum() { return mDataNum; }

	private:
		//indice struce
		//1(uint32)
		void* mData;
		uint64 mDataNum;
	};


}


#endif // !_WING_ENGINE_INDEICE_DATA_H_