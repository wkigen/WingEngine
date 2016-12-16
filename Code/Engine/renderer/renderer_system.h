#ifndef _WING_ENGINE_RENDERER_SYSTEM_H_
#define _WING_ENGINE_RENDERER_SYSTEM_H_

#include "common\engine_defines.h"
#include "base\singleton.h"
#include <map>
#include "renderer_context.h"
#include "renderable.h"
#include <queue>

namespace WingEngine
{

	class WING_ENGINE_API RendererSystem :public WingCore::Singleton<RendererSystem>
	{
		friend class WingCore::Singleton<RendererSystem>;

	public:
		~RendererSystem();

		bool create(void* windowHandle,uint32 width, uint32 height);
		void destroy();

		void render();


		void addRenderable(Renderable* able);

	private:
		RendererSystem();
		
	private:
		std::string								mRendererName;
		RendererContext*						mRendererContext;
		bool									mCreate;
		std::map<std::string, RendererContext*> mRendererContexts;
		uint32									mWidth;
		uint32									mHeight;
		std::queue<Renderable*>					mRenderables;

	};
}

#endif