#ifndef _WING_ENGINE_PROGRAM_H_
#define _WING_ENGINE_PROGRAM_H_

#include "common\defines.h"
#include "common\engine_defines.h"
#include <string>

namespace WingEngine
{
	class WING_ENGINE_API Program
	{

	public:
		Program();
		~Program();
		virtual void create(std::string vs,std::string fs)=0;
		virtual void use() = 0;
		virtual void destroy()=0;

		uint32 getProgramID() { return mProgramID; }

	protected:
		uint32 mProgramID;
	};

}


#endif