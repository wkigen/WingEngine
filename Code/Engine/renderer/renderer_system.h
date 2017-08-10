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
#include "light\light.h"

namespace WingEngine
{

	class WING_ENGINE_API RendererSystem :public WingCore::Singleton<RendererSystem>
	{
		friend class WingCore::Singleton<RendererSystem>;

	public:
		~RendererSystem();

		bool				create(void* windowHandle, uint32 width, uint32 height);
		void				destroy();

		void				sort();
		void				render();

		void				addRenderable(SmartPtr<Renderable> able);

		SmartPtr<RenderPass>getRenderPass(std::string name);

		SmartPtr<Camera>	getCamera() { return mCamera; }

		RendererContext*	getRendererContext() { return mRendererContext; }

		uint32				getWidth() { return mWidth; }
		uint32				getHeight() { return mHeight; }

		void				enableShadow(bool enable) { mIsShadow = enable; }
		bool				getEnableShadow() { return mIsShadow; }

		void				enableLight(bool enable) { mIsLight = enable; }
		bool				getEnableLight() { return mIsLight; }

		SmartPtr<Program>	createProgram(std::string name,std::string verFileName, std::string fraFileName);
		void				addProgram(std::string name, SmartPtr<Program> program);
		void				useProgram(std::string name);
		SmartPtr<Program>	getProgram(std::string name);

		int8				getLightsData(int32* type,real* postion,real* direction,real* color);
		SmartPtr<Light>		getLight(uint8 index);
		SmartPtr<Light>		getLight(std::string name);
		void				addLight(std::string name, SmartPtr<Light> light);
		

	private:
		RendererSystem();

		void				realRender();
	private:
		bool											mCreate;
		bool											mIsShadow;
		bool											mIsLight;

		SmartPtr<Camera>								mCamera;

		std::string										mRendererName;
		RendererContext*								mRendererContext;
		std::map<std::string, RendererContext*>			mRendererContexts;

		SmartPtr<RenderPass>							mCurrRenderPass;
		std::map<std::string, SmartPtr<RenderPass>>		mRenderPass;

		uint32											mWidth;
		uint32											mHeight;

		std::list<SmartPtr<Renderable>>					mRenderables;
	
		std::map<std::string,SmartPtr<Program>>			mPrograms;
		SmartPtr<Program>								mCurrProgram;

		std::map<std::string, SmartPtr<Light>>			mLights;
	};
}

#endif