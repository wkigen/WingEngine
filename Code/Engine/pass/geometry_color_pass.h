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
		virtual void preRender();
		virtual void render(Renderable* renderable);
		virtual void postRender();

	protected:
		virtual void _render(Renderable* renderable);

	};


}

#endif