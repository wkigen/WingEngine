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

#include "pass\base_render_pass.h"
#include "pass\geometry_color_pass.h"
#include "pass\geometry_texture_pass.h"
#include "pass\geometry_texture_light_pass.h"
#include "pass\geometry_texture_light_shadow_first_pass.h"
#include "pass\geometry_texture_light_shadow_second_pass.h"

using namespace WingCore;

namespace WingEngine
{
	RendererSystem::RendererSystem()
		:mCreate(false)
		,mWidth(0)
		,mHeight(0)
		,mIsShadow(true)
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
		mCamera = WING_NEW Camera();
		mCamera->setCamera(45,(real)mWidth /(real)mHeight, 1, 10, eye, view, up);

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
		mPrograms["geometry_texture_light"]= mRendererContext->createProgram("geometry_texture_light", geometry_texture_light_vs, geometry_texture_light_fs);
		mPrograms["base_render"] = createProgram("base_render", "res/shader/base_render.vert", "res/shader/base_render.frag");
		mPrograms["shadow_map_first"] = createProgram("shadow_map_first", "res/shader/shadow_map_first.vert", "res/shader/shadow_map_first.frag");
		mPrograms["shadow_map_second"] = createProgram("shadow_map_second", "res/shader/shadow_map_second.vert", "res/shader/shadow_map_second.frag");

		useProgram("base");
		mRendererContext->enableDepth(true);

		//SmartPtr<GeometryColorPass> geometryPass = WING_NEW GeometryColorPass();
		//geometryPass->init();
		//mRenderPass["GeometryPass"] = geometryPass;

		//SmartPtr<GeometryTexturePass> geometryTexturePass = WING_NEW GeometryTexturePass();
		//geometryTexturePass->init();
		//mRenderPass["GeometryTexturePass"] = geometryTexturePass;
	
		//SmartPtr<GeometryTextureLightPass> geometryTextureLightPass = WING_NEW GeometryTextureLightPass();
		//geometryTextureLightPass->init();
		//mRenderPass["GeometryTextureLightPass"] = geometryTextureLightPass;

		SmartPtr<GeometryTextureLightShadowFirstPass> geometryTextureLightShadowFirstPass = WING_NEW GeometryTextureLightShadowFirstPass(mWidth,mHeight);
		geometryTextureLightShadowFirstPass->init();
		mRenderPass["GeometryTextureLightShadowFirstPass"] = geometryTextureLightShadowFirstPass;

		SmartPtr<GeometryTextureLightShadowSecondPass> geometryTextureLightSecondShadowPass = WING_NEW GeometryTextureLightShadowSecondPass();
		geometryTextureLightSecondShadowPass->init();
		mRenderPass["GeometryTextureLightShadowSecondPass"] = geometryTextureLightSecondShadowPass;

		SmartPtr<BaseRenderPass> baseRenderPass = WING_NEW BaseRenderPass();
		baseRenderPass->init();
		mRenderPass["BaseRenderPass"] = baseRenderPass;

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
	bool fff = false;
	void RendererSystem::render()
	{
		
		mRendererContext->clear();
		if (mIsShadow)
		{
			RenderPass* pass = getRenderPass("GeometryTextureLightShadowFirstPass");
			GeometryTextureLightShadowFirstPass* firstPass = static_cast<GeometryTextureLightShadowFirstPass*>(pass);
			firstPass->preRender();

			std::list<SmartPtr<Renderable>>::iterator beg = mRenderables.begin();
			for (; beg != mRenderables.end(); beg++)
			{
				firstPass->render(*beg);
			};

			firstPass->postRender();

			SmartPtr<Texture> depthTexture = firstPass->getColorTexture();
			
			//if (!fff)
			//{
			//	real* data = new real[800 * 600 * 3];
			//	mRendererContext->getTextureData(depthTexture->getGPUBufferId(), ColorFormatRGB, DataElementReal, data);
			//	for (size_t i = 0; i < 800 * 600 * 3; i++)
			//	{
			//		WING_LOG_ERROR("%f", data[i]);
			//	}
			//	fff = true;
			//}

			mRendererContext->bindRenderTarget(INVALID_BUFFERS);

			RenderPass* pass2 = getRenderPass("GeometryTextureLightShadowSecondPass");
			GeometryTextureLightShadowSecondPass* secondPass = static_cast<GeometryTextureLightShadowSecondPass*>(pass2);

			secondPass->setDepthTexture(depthTexture);

			secondPass->preRender();

			std::list<SmartPtr<Renderable>>::iterator beg2 = mRenderables.begin();
			for (; beg2 != mRenderables.end(); beg2++)
			{
				secondPass->render(*beg2);
			};

			secondPass->postRender();
		}
		else
		{
			realRender();
		}

		mRenderables.clear();
		mRendererContext->swapBuffers();
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

	int8 RendererSystem::getLightsData(int32* type, real* postion, real* direction, real* color)
	{
		int8 count = 0;
		std::map<std::string, SmartPtr<Light>>::iterator iter = mLights.begin();
		for (; iter != mLights.end(); iter++)
		{
			SmartPtr<Light> light = iter->second;

			*type++ = light->getLightType();

			*postion++ = light->getPosition().x;
			*postion++ = light->getPosition().y;
			*postion++ = light->getPosition().z;

			*direction++ = light->getDirection().x;
			*direction++ = light->getDirection().y;
			*direction++ = light->getDirection().z;

			*color++ = light->getColor().r;
			*color++ = light->getColor().g;
			*color++ = light->getColor().b;
			*color++ = light->getColor().a;

			count++  ;
		}

		return count;
	}

	SmartPtr<Light> RendererSystem::getLight(uint8 index)
	{
		std::map<std::string, SmartPtr<Light>>::iterator iter = mLights.begin();
		int8 count = 0;
		for (; iter!= mLights.end(); iter++)
		{
			if (count == index)
			{
				return iter->second;
			}
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