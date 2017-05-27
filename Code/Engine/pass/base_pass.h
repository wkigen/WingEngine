#ifndef _WING_ENGINE_BASE_PASS_H_
#define _WING_ENGINE_BASE_PASS_H_

#include "renderer\program.h"
#include "renderer\render_pass.h"

namespace WingEngine
{

	class BasePass : public RenderPass
	{

	public:

		BasePass(Renderable* renderable);
		~BasePass();

		virtual void init();
		virtual void bind();
		virtual void unBind();

	protected:

		Program* mProgram;
		int32 mAttribPosition;
		int32 mUniformModelMatrix;
		int32 mUniformProjectdViewMatrix;

	};


}

#endif