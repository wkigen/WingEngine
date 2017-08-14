#ifndef _WING_ENGINE_LIGHT_H_
#define _WING_ENGINE_LIGHT_H_

#include "common\constant.h"
#include "scene\node.h"
#include "renderer\color.h"
#include "math\vector.h"

namespace WingEngine
{

	class WING_ENGINE_API Light : public Node
	{

	public:
		Light();
		~Light();

		virtual LightType getLightType() { return mLightType; }

		virtual bool getEnable();
		virtual void setEnable(bool enable);

		virtual void setRange(real range);
		virtual real getRange();

		virtual void setColor(Color color);
		virtual Color getColor();

		virtual void setDirection(Vectorf direction) { mDirection = direction; }
		virtual Vectorf getDirection() { return mDirection; }

		virtual void setShiness(real shiness) { mShiness = shiness; }
		virtual real getShiness() { return mShiness; }
	protected:

		LightType	mLightType;
		uint8		mShiness;
		real		mRange;
		Color		mColor;
		bool		mEnable;
		Vectorf		mDirection;
		

	};

}


#endif