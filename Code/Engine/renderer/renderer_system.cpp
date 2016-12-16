#include "renderer_system.h"
#include "log\log.h"
#include "dll\dll_system.h"
#include "common\constant.h"
#include "shader\test_shader.h"

namespace WingEngine
{
	RendererSystem::RendererSystem()
		:mCreate(false)
		,mWidth(0)
		,mHeight(0)
	{

	}

	RendererSystem::~RendererSystem()
	{

	}

	bool RendererSystem::create(void* windowHandle,uint32 width,uint32 height)
	{
		if (mCreate)
		{
			WING_LOG_WARN("DllSystem has been create");
			return false;
		}
		mCreate = true;
		mWidth = width;
		mHeight = height;

		std::list<WingCore::Module*> rendererDll = WingCore::DllSystem::getInstance()->getMoudles(ModuleTypeRenderer);
		std::list<WingCore::Module*>::iterator iter = rendererDll.begin();

		while (iter != rendererDll.end())
		{
			RendererContext* context = (RendererContext*)(*iter)->mObject;
			if (context)
			{
				context->create(windowHandle, mWidth, mHeight);
				mRendererContexts[(*iter)->mName] = context;
			}
			iter++;
		}

		if (mRendererContexts.size() == 0)
		{
			WING_LOG_WARN("no RendererContext !!");
			return false;
		}

		mRendererName = mRendererContexts.begin()->first;
		mRendererContext = mRendererContexts.begin()->second;

		mRendererContext->createProgram("test", test_vs, test_fs);
		mRendererContext->useProgram("test");

		return true;
	}

	void RendererSystem::destroy()
	{
		std::map<std::string, RendererContext*>::iterator iter = mRendererContexts.begin();
		while (iter != mRendererContexts.end())
		{
			iter->second->destroy();
			iter++;
		}
	}

	void RendererSystem::render()
	{
		while (!mRenderables.empty())
		{
			mRendererContext->render(mRenderables.front());
			mRenderables.pop();
		};
	}


	void RendererSystem::addRenderable(Renderable* able)
	{
		mRenderables.push(able);
	}
}