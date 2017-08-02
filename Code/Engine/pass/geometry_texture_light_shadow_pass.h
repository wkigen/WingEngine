#ifndef _WING_ENGINE_GEOMETRY_TEXTURE_LIGHT_SHADOW_PASS_H_
#define _WING_ENGINE_GEOMETRY_TEXTURE_LIGHT_SHADOW_PASS_H_

#include "base_pass.h"

namespace WingEngine
{

	class GeometryTextureLightShadowPass : public BasePass
	{

	public:

		GeometryTextureLightShadowPass(uint32 width,uint32 height);
		~GeometryTextureLightShadowPass();

		virtual void init();
		virtual void preRender(Renderable* renderable);
		virtual void render(Renderable* renderable);
		virtual void postRender();

	protected:
		uint32 mWidth;
		uint32 mHeight;
		SmartPtr<Texture> mTexture;
		SmartPtr<RenderTarget> mRenderTarget;

		SmartPtr<Texture> mDepthTexture;
		SmartPtr<RenderTarget> mDepthRenderTarget;
	};


}

#endif