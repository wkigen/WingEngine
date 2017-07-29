#ifndef _WING_ENGINE_GEOMETRY_PASS_H_
#define _WING_ENGINE_GEOMETRY_PASS_H_

#include "base_pass.h"

namespace WingEngine
{

	class GeometryPass : public BasePass
	{

	public:

		GeometryPass();
		~GeometryPass();

		virtual void init();
		virtual void bind(Renderable* renderable);
		virtual void unBind();

	protected:
		int32 mAttribColor;

	};


}

#endif