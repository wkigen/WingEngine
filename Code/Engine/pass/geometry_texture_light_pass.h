#ifndef _WING_ENGINE_GEOMETRY_TEXTURE_LIGHT_PASS_H_
#define _WING_ENGINE_GEOMETRY_TEXTURE_LIGHT_PASS_H_

#include "base_pass.h"

namespace WingEngine
{

	class GeometryTextureLightPass : public BasePass
	{

	public:

		GeometryTextureLightPass();
		~GeometryTextureLightPass();

		virtual void init();
		virtual void bind(Renderable* renderable);
		virtual void unBind();

	protected:


	};


}

#endif