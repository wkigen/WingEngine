#ifndef _WING_ENGINE_FONT_PASS_H_
#define _WING_ENGINE_FONT_PASS_H_

#include "base_pass.h"

namespace WingEngine
{

	class FontBasePass : public BasePass
	{

	public:

		FontBasePass();
		~FontBasePass();

		virtual void init();
		virtual void preRender();
		virtual void render(Renderable* renderable);
		virtual void postRender();

	protected:
	
		virtual void _render(Renderable* renderable);

	protected:

	};


}

#endif