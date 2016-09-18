#ifndef _WING_ENGINE_PROGRAM_H_
#define _WING_ENGINE_PROGRAM_H_

#include "common\engine_defines.h"
#include <string>

namespace WingEngine
{
	class WING_ENGINE_API Program
	{

	public:
		virtual void create(std::string vs,std::string fs)=0;
		virtual void use() = 0;
		virtual void destroy()=0;

	};

}


#endif