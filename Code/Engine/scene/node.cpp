#include "node.h"
#include "log\log.h"

namespace WingEngine
{
	Node::Node()
		:mRenderType(RenderTypeNULL)
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


	void Node::translation(const Vectorf &t)
	{
		Matrix44 traMatrix44;
		traMatrix44.setTranslation(t);
		mModelMatrix44 *= traMatrix44;
	}

	void Node::rotate(const Vectorf &t)
	{
		Matrix44 rotMatrix44;
		rotMatrix44.setRotate(t);
		mModelMatrix44 *= rotMatrix44;
	}

	void Node::scale(const Vectorf &t)
	{
		Matrix44 scaMatrix44;
		scaMatrix44.setScale(t);
		mModelMatrix44 *= scaMatrix44;
	}
}