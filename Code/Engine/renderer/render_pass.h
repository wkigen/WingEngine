#ifndef _WING_ENGINE_RENDER_PASS_H_
#define _WING_ENGINE_RENDER_PASS_H_

#include "base\object.h"
#include "common\engine_defines.h"

using namespace WingCore;


namespace WingEngine
{

	class Renderable;

	class WING_ENGINE_API RenderPass : public Object
	{
	public:

		RenderPass(Renderable* renderable) ;
		~RenderPass();

		virtual void init() = 0;

		virtual void bind() = 0;
		virtual void unBind() = 0;

	protected:

		Renderable* mRenderable;

	};


}

#endif