#ifndef _WING_ENGINE_RENDERABLE_H_
#define _WING_ENGINE_RENDERABLE_H_

#include "scene\node.h"

namespace WingEngine
{


	class WING_ENGINE_API Renderable : public Node
	{

	public:
		Renderable(Node* parentNode);
		~Renderable();


	};


}

#endif