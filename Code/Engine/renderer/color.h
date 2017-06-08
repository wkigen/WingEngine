#ifndef _WING_ENGINE_COLOR_H_
#define _WING_ENGINE_COLOR_H_

#include "common\engine_defines.h"

namespace WingEngine
{

	class WING_ENGINE_API Color 
	{

	public:
		Color(float r=0,float g=0,float b=0,float a=1);
		~Color();



		float r, g, b, a;

	};

}


#endif