#ifndef _WING_ENGINE_NODE_H_
#define _WING_ENGINE_NODE_H_

#include "common\engine_defines.h"
#include "math\matrix44.h"
#include "math\matrix44_cal.h"
#include <map>

using namespace WingCore;


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

		virtual Matrix44		getModelViewMatrinx44() { return mModelMatrix44; }

		virtual void			translation(const Vectorf &t);
		virtual void			rotate(const Vectorf &t);

	protected:

		std::string						mName;
		Node*							mParentNode;
		std::map<std::string, Node*>	mChildren;
		Matrix44						mModelMatrix44;
	};

}

#endif