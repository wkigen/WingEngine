#ifndef _WING_ENGINE_FONT_PLANE_H_
#define _WING_ENGINE_FONT_PLANE_H_

#include "geometry.h"
#include "common\engine_defines.h"

namespace WingEngine
{

	class WING_ENGINE_API FontPlane :public Geometry
	{
	public:

		FontPlane();
		~FontPlane();

		virtual void bindText();
	};


}


#endif