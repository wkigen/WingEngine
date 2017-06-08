#include "light.h"

namespace WingEngine
{
	Light::Light()
		:mEnable(false)
	{

	}

	Light::~Light()
	{

	}

	bool Light::getEnable()
	{
		return mEnable;
	}

	void Light::setEnable(bool enable)
	{
		mEnable = enable;
	}

	void Light::setRange(real range)
	{
		mRange = range;
	}

	real Light::getRange()
	{
		return mRange;
	}

	void Light::setColor(Color color)
	{
		mColor = color;
	}

	Color Light::getColor()
	{
		return mColor;
	}

}