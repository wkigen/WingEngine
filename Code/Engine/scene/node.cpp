#include "node.h"
#include "log\log.h"

namespace WingEngine
{
	Node::Node()
	{

	}

	Node::~Node()
	{

	}


	void Node::setName(std::string name)
	{
		mName = name;
	}

	std::string Node::getName()
	{
		return mName;
	}

	void Node::addChild(Node* child)
	{
		std::map<std::string, Node*>::iterator itor = mChildren.find(child->getName());
		if (itor != mChildren.end())
		{
			WING_LOG_ERROR("have child name [%s] in the node ", child->getName().c_str());
			return;
		}

		mChildren[child->getName()] = child;
	}

	Node* Node::getChild(std::string name)
	{
		std::map<std::string, Node*>::iterator itor = mChildren.find(name);
		if (itor != mChildren.end())
		{
			return itor->second;
		}
		WING_LOG_ERROR("can not find the child [%s]",name.c_str());
		return nullptr;
	}
}