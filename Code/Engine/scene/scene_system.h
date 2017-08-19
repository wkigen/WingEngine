#ifndef _WING_ENGINE_SCENE_SYSTEM_H_
#define _WING_ENGINE_SCENE_SYSTEM_H_

#include "base\singleton.h"
#include "common\engine_defines.h"
#include "node.h"
#include <map>

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

		void addNode(std::string name, SmartPtr<Node> node);

		SmartPtr<Node> findNode(std::string name);

		void removeNode(std::string name);

		void addNodeToRenderer();

	private:
		SceneSystem();

	private:

		bool				mCreate;
		Node*				mRootNode;
		std::map<std::string, SmartPtr<Node>> mNode;
		
	};

}



#endif