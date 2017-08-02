#include "renderer_system.h"
#include "log\log.h"
#include "plugin\plugin_system.h"
#include "common\constant.h"
#include "shader\test_shader.h"
#include "allocator\allocator.h"
#include "pass\geometry_color_pass.h"
#include "pass\geometry_texture_pass.h"
#include "pass\geometry_texture_light_pass.h"
#include "pass\geometry_texture_light_shadow_pass.h"

using namespace WingCore;

namespace WingEngine
{
	RendererSystem::RendererSystem()
		:mCreate(false)
		,mWidth(0)
		,mHeight(0)
		,mIsShadow(false)
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

		Pointf eye(0, 4, 4);
		Pointf view(0, 0, 0);
		Vectorf up(0, 1, 0);
		mCamera.setCamera(45,(real)mWidth /(real)mHeight, 1, 10, eye, view, up);

		std::list<Plugin*> rendererDll = PluginSystem::getInstance()->getPlugin(PluginTypeRenderer);
		std::list<Plugin*>::iterator iter = rendererDll.begin();

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

		mRendererContext->enableDepth(true);

		SmartPtr<GeometryColorPass> geometryPass = WING_NEW GeometryColorPass();
		geometryPass->init();
		mRenderPass["GeometryPass"] = geometryPass;

		SmartPtr<GeometryTexturePass> geometryTexturePass = WING_NEW GeometryTexturePass();
		geometryTexturePass->init();
		mRenderPass["GeometryTexturePass"] = geometryTexturePass;
	
		SmartPtr<GeometryTextureLightPass> geometryTextureLightPass = WING_NEW GeometryTextureLightPass();
		geometryTextureLightPass->init();
		mRenderPass["GeometryTextureLightPass"] = geometryTextureLightPass;

		SmartPtr<GeometryTextureLightShadowPass> geometryTextureLightShadowPass = WING_NEW GeometryTextureLightShadowPass(mWidth,mHeight);
		geometryTextureLightShadowPass->init();
		mRenderPass["GeometryTextureLightShadowPass"] = geometryTextureLightShadowPass;

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
		if (mIsShadow)
		{

		}
		else
		{
			std::list<SmartPtr<Renderable>>::iterator beg = mRenderables.begin();
			SmartPtr<RenderPass> lastRenderPass;
			for (; beg != mRenderables.end(); beg++)
			{
				SmartPtr<RenderPass> currRenderPass = (*beg)->getRenderPass();
				if(currRenderPass != lastRenderPass)
					currRenderPass->preRender();

				currRenderPass->render(*beg);

				if (currRenderPass != lastRenderPass)
					currRenderPass->postRender();

				lastRenderPass = currRenderPass;
			};
			mRenderables.clear();
			mRendererContext->swapBuffers();
		}
	}

	void RendererSystem::addRenderable(Renderable* able)
	{
		mRenderables.push_back(able);
	}


	BasePass* RendererSystem::getRenderPass(std::string name)
	{
		std::map<std::string, SmartPtr<BasePass>>::iterator iter = mRenderPass.find(name);
		if (iter != mRenderPass.end())
		{
			return iter->second;
		}
		return nullptr;
	}

}