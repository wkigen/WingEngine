#ifndef _WING_ENGINE_BASE_RENDER_PASS_H_
#define _WING_ENGINE_BASE_RENDER_PASS_H_

#include "pass\base_pass.h"
#include "renderer\program.h"
#include "renderer\render_target.h"

namespace WingEngine
{

	class BaseRenderPass : public BasePass
	{

	public:

		BaseRenderPass();
		~BaseRenderPass();

		virtual void init();
		virtual void preRender();
		virtual void render(Renderable* renderable);
		virtual void postRender();

	protected:


	};


}

#endif