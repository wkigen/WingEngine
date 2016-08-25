#ifndef _WING_ENGINE_RENDERER_SYSTEM_H_
#define _WING_ENGINE_RENDERER_SYSTEM_H_

#include "common\engine_defines.h"
#include "base\singleton.h"
#include <map>
#include "renderer_context.h"

namespace WingEngine
{

	class WING_ENGINE_API RendererSystem :public WingCore::Singleton<RendererSystem>
	{
		friend class WingCore::Singleton<RendererSystem>;

	public:
		~RendererSystem();

		bool create();
		void destroy();

	private:
		RendererSystem();
		
	private:
		bool				mCreate;
		std::map<std::string, RendererContext*> mRendererContexts;

	};
}

#endif