#ifndef _WING_ENGINE_CHARACTER_H_
#define _WING_ENGINE_CHARACTER_H_

#include "base\object.h"
#include "renderer\texture.h"

namespace WingEngine
{

	class WING_ENGINE_API Character :public WingCore::Object
	{

	public:

		Character(SmartPtr<Texture> texture, uint32 width, uint32 height, uint32 bearingLeft, uint32 bearingTop, uint32 advance);
		~Character();

		SmartPtr<Texture> getTexture() { return mTexture; }

		uint32 getWidth() { return mWidth; }
		uint32 getHeight() { return mHeight; }

		uint32 getBearingLeft() { return mBearingLeft; }
		uint32 getBearingTop() { return mBearingTop; }

		uint32 getAdvance() { return mAdvance; }

	private:

		SmartPtr<Texture> mTexture;

		uint32 mWidth;
		uint32 mHeight;
		uint32 mBearingLeft;		// 字形基于基线的left
		uint32 mBearingTop;			// 字形基于基线的top
		uint32 mAdvance;			// 起点到下一个字形起点的距离

	};

}

#endif