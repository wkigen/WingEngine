#ifndef _WING_ENGINE_BASE_PASS_H_
#define _WING_ENGINE_BASE_PASS_H_

#include "renderer\program.h"
#include "renderer\render_pass.h"
#include "renderer\render_target.h"

namespace WingEngine
{

	class BasePass : public RenderPass
	{

	public:

		BasePass();
		~BasePass();

		virtual void init();
		virtual void preRender();
		virtual void render(Renderable* renderable);
		virtual void postRender();

	protected:

		Program* mProgram;

		int32 mAttribColor;
		int32 mAttribPosition;
		int32 mAttribNormal;

		int32 mUniformModelMatrix;
		int32 mUniformProjectdViewMatrix;
		int32 mUniformTransposeInverseMatrix;
		int32 mAttribTextureCoordinate;
		int32 mUniformTexture;
		int32 mUniformViewPosition;

		int32 mUniformShiness;
		int32 mUniformAmbient;
		int32 mUniformDiffuse;
		int32 mUniformSpecular;


	};


}

#endif