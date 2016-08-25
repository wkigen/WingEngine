#ifndef _WING_ENGINE_RENDERER_CONTEXT_H_
#define _WING_ENGINE_RENDERER_CONTEXT_H_

#include "common\engine_defines.h"


namespace WingEngine
{

	class WING_ENGINE_API RendererContext
	{

	public:
		RendererContext() {};
		virtual ~RendererContext() {};


		virtual bool create() = 0;
		virtual void destroy() = 0;

	private:

	};
}


#endif