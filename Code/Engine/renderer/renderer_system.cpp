#include "renderer_system.h"
#include "log\log.h"
#include "plugin\plugin_system.h"
#include "common\constant.h"
#include "allocator\allocator.h"
#include "io\file_system.h"

#include "shader\test_shader.h"
#include "shader\base_shader.h"
#include "shader\geometry_color_shader.h"
#include "shader\geometry_texture_light_shader.h"
#include "shader\geometry_texture_shader.h"

#include "pass\geometry_color_pass.h"
#include "pass\geometry_texture_pass.h"
#include "pass\geometry_texture_light_pass.h"
#include "pass\geometry_texture_light_shadow_first_pass.h"

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

		mPrograms["base"] = mRendererContext->createProgram("test", base_vs, base_fs);
		mPrograms["geometry_color"] = mRendererContext->createProgram("geometry_color", geometry_color_vs, geometry_color_fs);
		mPrograms["geometry_texture"]= mRendererContext->createProgram("geometry_texture", geometry_texture_vs, geometry_texture_fs);
		//mPrograms["geometry_texture_light"]= mRendererContext->createProgram("geometry_texture_light", geometry_texture_light_vs, geometry_texture_light_fs);
		mPrograms["geometry_texture_light"] = createProgram("geometry_texture_light", "res/shader/geometry_texture_light_shadow.vert", "res/shader/geometry_texture_light_shadow.frag");

		useProgram("base");
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

		SmartPtr<GeometryTextureLightShadowFirstPass> geometryTextureLightShadowPass = WING_NEW GeometryTextureLightShadowFirstPass(mWidth,mHeight);
		geometryTextureLightShadowPass->init();
		mRenderPass["GeometryTextureLightShadowFirstPass"] = geometryTextureLightShadowPass;

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
	SmartPtr<Program> RendererSystem::createProgram(std::string name, std::string verFileName, std::string fraFileName)
	{
		FileStream verStream,fraStream;
		if (!FileSystem::getInstance()->openFile(verFileName, verStream, ACCESS::Read))
			return nullptr;
		if (!FileSystem::getInstance()->openFile(fraFileName, fraStream, ACCESS::Read))
			return nullptr;

		int8 *verStr,*fraStr;
		uint64 verSize = verStream.getSize();
		verStr = (int8*)WING_ALLOC(verSize +1);
		verStream.read(verStr, verSize);
		verStr[verSize] = '\0';

		uint64 fraSize = fraStream.getSize();
		fraStr = (int8*)WING_ALLOC(fraSize+1);
		fraStream.read(fraStr, fraSize);
		fraStr[fraSize] = '\0';

		SmartPtr<Program> program = mRendererContext->createProgram(name, verStr, fraStr);
		addProgram(name, program);

		WING_FREE(verStr);
		WING_FREE(fraStr);

		return program;
	}

	void RendererSystem::addProgram(std::string name, SmartPtr<Program> program)
	{
		if (program != nullptr)
		{
			if (mPrograms.find(name) != mPrograms.end())
			{
				WING_LOG_WARN("is has same name [%s] in programs list", name.c_str());
				return;
			}
			mPrograms[name] = program;
		}
	}

	void RendererSystem::useProgram(std::string name)
	{
		Program* program = getProgram(name);
		if (program != nullptr)
		{
			mCurrProgram = program;
			mCurrProgram->use();
		}
	}

	SmartPtr<Program> RendererSystem::getProgram(std::string name)
	{
		std::map<std::string, SmartPtr<Program>>::iterator itor = mPrograms.find(name);
		if (itor != mPrograms.end())
		{
			return itor->second;
		}
		return nullptr;
	}

	void RendererSystem::sort()
	{

	}

	void RendererSystem::render()
	{
		
		mRendererContext->clear();
		if (mIsShadow)
		{
			RenderPass* pass = getRenderPass("GeometryTextureLightShadowFirstPass");
			GeometryTextureLightShadowFirstPass* firstPass = static_cast<GeometryTextureLightShadowFirstPass*>(pass);
			firstPass->preRender();

			realRender();

			firstPass->postRender();
			mRendererContext->swapBuffers();

			Texture* depthTexture = firstPass->getDepthTexture();
			Texture* colorTexture = firstPass->getColorTexture();

		}
		else
		{
			realRender();
			mRendererContext->swapBuffers();
		}

		mRenderables.clear();
	}

	void RendererSystem::realRender()
	{
		std::list<SmartPtr<Renderable>>::iterator beg = mRenderables.begin();
		SmartPtr<RenderPass> lastRenderPass;
		for (; beg != mRenderables.end(); beg++)
		{
			SmartPtr<RenderPass> currRenderPass = (*beg)->getRenderPass();
			if (currRenderPass != lastRenderPass)
				currRenderPass->preRender();

			currRenderPass->render(*beg);

			if (currRenderPass != lastRenderPass)
				currRenderPass->postRender();

			lastRenderPass = currRenderPass;
		};
	}

	void RendererSystem::addRenderable(SmartPtr<Renderable> able)
	{
		mRenderables.push_back(able);
	}


	SmartPtr<RenderPass> RendererSystem::getRenderPass(std::string name)
	{
		std::map<std::string, SmartPtr<RenderPass>>::iterator iter = mRenderPass.find(name);
		if (iter != mRenderPass.end())
		{
			return iter->second;
		}
		return nullptr;
	}

	SmartPtr<Light> RendererSystem::getLight(std::string name)
	{
		std::map<std::string, SmartPtr<Light>>::iterator iter = mLights.find(name);
		if (iter != mLights.end())
		{
			return iter->second;
		}
		return nullptr;
	}

	void RendererSystem::addLight(std::string name, SmartPtr<Light> light)
	{
		if (light != nullptr)
		{
			if (mLights.find(name) != mLights.end())
			{
				WING_LOG_WARN("is has same name [%s] in light list", name.c_str());
				return;
			}
			mLights[name] = light;
		}
	}

}