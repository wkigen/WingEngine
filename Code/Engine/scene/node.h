#ifndef _WING_ENGINE_NODE_H_
#define _WING_ENGINE_NODE_H_

#include "common\engine_defines.h"
#include <map>

namespace WingEngine
{

	class WING_ENGINE_API Node
	{

	public:
		Node();
		~Node();

		virtual void			setName(std::string name);
		virtual std::string		getName();

		virtual void			addChild(Node* child);
		virtual Node*			getChild(std::string name);

	protected:
		std::string						mName;
		Node*							mParentNode;
		std::map<std::string, Node*>	mChildren;
	};

}

#endif