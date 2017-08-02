#ifndef _WING_ENGINE_GEOMETRY_PASS_H_
#define _WING_ENGINE_GEOMETRY_PASS_H_

#include "base_pass.h"

namespace WingEngine
{

	class GeometryColorPass : public BasePass
	{

	public:

		GeometryColorPass();
		~GeometryColorPass();

		virtual void init();
		virtual void preRender(Renderable* renderable);
		virtual void postRender();

	protected:
		

	};


}

#endif