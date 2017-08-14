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
	
		virtual void _render(Renderable* renderable);

	protected:

		Program*			mProgram;

		int32 mAttribColor;
		int32 mAttribPosition;
		int32 mAttribNormal;

		int32 mTexture0;
		int32 mTexture1;
		int32 mTexture2;
		int32 mTexture3;
		int32 mTexture4;

		int32 mUniformModelMatrix;
		int32 mUniformProjectdViewMatrix;
		int32 mUniformTransposeInverseMatrix;
		int32 mAttribTextureCoordinate;
		int32 mUniformTexture;
		int32 mUniformViewPosition;

		int32 mUniformLightNum;
		int32 mUniformLightType;
		int32 mUniformLightPosition;
		int32 mUniformLightDirection;
		int32 mUniformLightColor;
		int32 mUniformLightMVPMatrix;

		int32 mUniformShiness;
		int32 mUniformAmbient;
		int32 mUniformDiffuse;
		int32 mUniformSpecular;

		int32 mLightNum;
		real *mShiness;
		int32 *mLightType;
		real *mLightPostion, *mLightDirection, *mLightColor;
	};


}

#endif