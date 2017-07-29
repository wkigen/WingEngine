#include "scene_system.h"
#include "io\file_system.h"
#include "plugin/plugin_system.h"
#include "log\log.h"
#include "allocator\allocator.h"
#include "renderer\renderer_system.h"

namespace WingEngine
{
	SceneSystem::SceneSystem()
		:mCreate(false)
	{

	}

	SceneSystem::~SceneSystem()
	{
		
	}

	bool SceneSystem::create()
	{
		if (mCreate)
		{
			WING_LOG_WARN("SceneSystem has been create");
			return false;
		}
		mCreate = true;

		mRootNode = WING_NEW Node();
		mRootNode->setName(ROOTNODE);

		return true;
	}

	void SceneSystem::destroy()
	{
		WING_DELETE(mRootNode);
	}

	void SceneSystem::addNode(std::string name, Node* node)
	{
		if (findNode(name) == nullptr)
		{
			mNode[name] = node;
		}
		else
		{
			WING_LOG_WARN("%s is exit",name.c_str());
		}
	}


	Node* SceneSystem::findNode(std::string name)
	{
		std::map<std::string, SmartPtr<Node>>::iterator iter = mNode.find(name);
		if (iter == mNode.end())
			return nullptr;

		return iter->second;
	}

	void SceneSystem::removeNode(std::string name)
	{
		std::map<std::string, SmartPtr<Node>>::iterator iter = mNode.find(name);
		if (iter != mNode.end())
		{
			mNode.erase(iter);
		}
	}

	void SceneSystem::addNodeToRenderer()
	{
		std::map<std::string, SmartPtr<Node>>::iterator beg = mNode.begin();
		for (;beg != mNode.end();beg++)
		{
			Node* node = beg->second;
			if (node->getRenderType() != RenderTypeNULL)
			{
				RendererSystem::getInstance()->addRenderable((Renderable*)node);
			}
			
		}
	}
}