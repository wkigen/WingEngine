#include "character.h"
#include "log\log.h"

namespace WingEngine
{

	Character::Character(SmartPtr<Texture> texture, uint32 width, uint32 height, uint32 bearingLeft, uint32 bearingTop, uint32 advance)
		:mTexture(texture)
		,mWidth(width)
		,mHeight(height)
		,mBearingLeft(bearingLeft)
		,mBearingTop(bearingTop)
		,mAdvance(advance)
	{
		
	}

	Character::~Character()
	{

	}

}