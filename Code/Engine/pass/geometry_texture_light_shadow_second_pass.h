#ifndef _WING_ENGINE_GEOMETRY_TEXTURE_LIGHT_SHADOW_SECOND_PASS_H_
#define _WING_ENGINE_GEOMETRY_TEXTURE_LIGHT_SHADOW_SECOND_PASS_H_

#include "base_pass.h"

namespace WingEngine
{

	class GeometryTextureLightShadowSecondPass : public BasePass
	{

	public:

		GeometryTextureLightShadowSecondPass();
		~GeometryTextureLightShadowSecondPass();

		virtual void init();
		virtual void preRender();
		virtual void render(Renderable* renderable);
		virtual void postRender();

	protected:


	};


}

#endif