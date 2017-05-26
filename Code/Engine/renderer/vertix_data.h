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

		virtual void* createData(uint64 num);

		virtual void* getData() { return mData; }

		virtual uint64 getDataNum() { return mDataNum; }

	private:
		//data struct
		//POSITION       NORMAL         TEXTURE_COORDINATE
		//3(real)        3(real)        2(real)
		void* mData;
		uint64 mDataNum;
	};


}


#endif // !_WING_ENGINE_VERTIX_DATA_H_