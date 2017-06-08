#ifndef _WING_ENGINE_LIGHT_H_
#define _WING_ENGINE_LIGHT_H_

#include "scene\node.h"
#include "renderer\color.h"

namespace WingEngine
{

	class WING_ENGINE_API Light : public Node
	{

	public:
		Light();
		~Light();

		virtual bool getEnable();
		virtual void setEnable(bool enable);

		virtual void setRange(real range);
		virtual real getRange();

		virtual void setColor(Color color);
		virtual Color getColor();

	protected:

		real mRange;
		Color mColor;
		bool mEnable;

	};

}


#endif