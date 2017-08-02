#ifndef _WING_ENGINE_GEOMETRY_TEXTURE_PASS_H_
#define _WING_ENGINE_GEOMETRY_TEXTURE_PASS_H_

#include "base_pass.h"

namespace WingEngine
{

	class GeometryTexturePass : public BasePass
	{

	public:

		GeometryTexturePass();
		~GeometryTexturePass();

		virtual void init();
		virtual void preRender();
		virtual void render(Renderable* renderable);
		virtual void postRender();

	protected:


	};


}

#endif