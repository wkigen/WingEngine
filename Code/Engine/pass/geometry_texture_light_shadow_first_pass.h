#ifndef _WING_ENGINE_GEOMETRY_TEXTURE_LIGHT_SHADOW_FIRST_PASS_H_
#define _WING_ENGINE_GEOMETRY_TEXTURE_LIGHT_SHADOW_FIRST_PASS_H_

#include "base_pass.h"

namespace WingEngine
{

	class GeometryTextureLightShadowFirstPass : public BasePass
	{

	public:

		GeometryTextureLightShadowFirstPass(uint32 width,uint32 height);
		~GeometryTextureLightShadowFirstPass();

		virtual void init();
		virtual void preRender();
		virtual void render(Renderable* renderable);
		virtual void postRender();

		virtual SmartPtr<Texture> getColorTexture() { return mColorTexture; }

		virtual SmartPtr<Texture> getDepthTexture() { return mDepthTexture; }

	protected:
		virtual void _render(Renderable* renderable);

	protected:

		uint32 mWidth;
		uint32 mHeight;

		SmartPtr<RenderTarget> mRenderTarget;
		SmartPtr<Texture> mColorTexture;

		SmartPtr<RenderTarget> mDepthRenderTarget;
		SmartPtr<Texture> mDepthTexture;
	};


}

#endif