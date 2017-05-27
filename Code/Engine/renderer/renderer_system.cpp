#include "renderer_system.h"
#include "log\log.h"
#include "dll\dll_system.h"
#include "common\constant.h"
#include "shader\test_shader.h"
#include "allocator\allocator.h"

using namespace WingCore;

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

		Pointf eye(0, 0, 3);
		Pointf view(0, 0, 0);
		Vectorf up(0, 1, 0);
		mCamera.setCamera(45,(real)mWidth /(real)mHeight, 1, 10, eye, view, up);

		std::list<WingCore::Module*> rendererDll = DllSystem::getInstance()->getMoudles(ModuleTypeRenderer);
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
		mRendererContext->clear();
		while (!mRenderables.empty())
		{
			mRendererContext->render(mRenderables.front());
			mRenderables.pop();
		};
		mRendererContext->swapBuffers();
	}


	void RendererSystem::addRenderable(Renderable* able)
	{
		mRenderables.push(able);
	}

}