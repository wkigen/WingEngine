#ifndef _WING_ENGINE_SCENE_SYSTEM_H_
#define _WING_ENGINE_SCENE_SYSTEM_H_

#include "base\singleton.h"
#include "common\engine_defines.h"
#include "node.h"

namespace WingEngine
{

#define ROOTNODE  "RootNode"

	class WING_ENGINE_API SceneSystem:public WingCore::Singleton<SceneSystem>
	{

		friend class WingCore::Singleton<SceneSystem>;

	public:
		virtual ~SceneSystem();

		bool create();
		void destroy();

	private:
		SceneSystem();

	private:

		bool				mCreate;

		Node*				mRootNode;
	};

}



#endif