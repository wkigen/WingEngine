#ifndef _WING_ENGINE_RENDERER_SYSTEM_H_
#define _WING_ENGINE_RENDERER_SYSTEM_H_

#include "common\engine_defines.h"
#include "base\singleton.h"
#include <map>
#include "renderer_context.h"
#include "renderable.h"
#include <queue>
#include "camera.h"
#include "pass\base_pass.h"

namespace WingEngine
{

	class WING_ENGINE_API RendererSystem :public WingCore::Singleton<RendererSystem>
	{
		friend class WingCore::Singleton<RendererSystem>;

	public:
		~RendererSystem();

		bool create(void* windowHandle, uint32 width, uint32 height);
		void destroy();

		void render();

		void addRenderable(Renderable* able);

		BasePass* getRenderPass(std::string name);

		Camera* getCamera() { return &mCamera; }

		RendererContext* getRendererContext() { return mRendererContext; }

		uint32 getWidth() { return mWidth; }
		uint32 getHeight() { return mHeight; }

		void enableShadow(bool enable) { mIsShadow = enable; }
		bool getEnableShadow() { return mIsShadow; }

	private:
		RendererSystem();

	private:
		bool											mCreate;
		bool											mIsShadow;
		Camera											mCamera;

		std::string										mRendererName;
		RendererContext*								mRendererContext;
		std::map<std::string, RendererContext*>			mRendererContexts;

		SmartPtr<BasePass>								mCurrRenderPass;
		std::map<std::string, SmartPtr<BasePass>>		mRenderPass;

		uint32											mWidth;
		uint32											mHeight;

		std::list<SmartPtr<Renderable>>					mRenderables;
	

	};
}

#endif