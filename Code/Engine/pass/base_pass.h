#ifndef _WING_ENGINE_BASE_PASS_H_
#define _WING_ENGINE_BASE_PASS_H_

#include "renderer\program.h"
#include "renderer\render_pass.h"

namespace WingEngine
{

	class BasePass : public RenderPass
	{

	public:

		BasePass();
		~BasePass();

		virtual void init();
		virtual void bind(Renderable* renderable);
		virtual void unBind();

	protected:

		Program* mProgram;
		int32 mAttribPosition;
		int32 mAttribNormal;
		int32 mUniformModelMatrix;
		int32 mUniformProjectdViewMatrix;
		int32 mUniformTransposeInverseMatrix;
		int32 mAttribTextureCoordinate;
		int32 mUniformTexture;
		int32 mAttribColor;
		int32 mUniformViewPosition;

	};


}

#endif