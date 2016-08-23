#ifndef _WING_CORE_WINDOW_H_
#define _WING_CORE_WINDOW_H_

#include "common\platform.h"
#include "common\defines.h"

namespace WingCore
{

#define WING_WINDOW_WIDTH	1280
#define WING_WINDOW_HEIGHT	720


	class WING_CORE_API Window
	{
	public:
		Window();
		~Window();

		virtual bool init() = 0;
		virtual void destriy() = 0;
		virtual void adjust(uint32 _width, uint32 _height) = 0;
		virtual void setWindowPos(uint32 x, uint32 y) = 0;

		inline void* getHandle() { return mHandle; };
		inline uint32 getWidth() { return mWidth; };
		inline uint32 getHeight() { return mHeight; };
	protected:
		void*	mHandle;
		uint32	mWidth;
		uint32	mHeight;
	};

}


#endif