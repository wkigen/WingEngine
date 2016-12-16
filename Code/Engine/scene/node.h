#ifndef _WING_ENGINE_NODE_H_
#define _WING_ENGINE_NODE_H_

#include "common\engine_defines.h"

namespace WingEngine
{

	class WING_ENGINE_API Node
	{

	public:
		Node(Node* parentNode);
		~Node();


	protected:

		Node* mParentNode;
	};

}

#endif