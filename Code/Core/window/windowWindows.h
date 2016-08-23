#ifndef _WING_CORE_WINDOW_WINDOWS_H_
#define _WING_CORE_WINDOW_WINDOWS_H_

#include"window.h"
#include "common\defines.h"

namespace WingCore
{

	class WING_CORE_API WindowWindows:public Window
	{
	public:

		WindowWindows();
		~WindowWindows();

		virtual bool init();
		virtual void destriy();
		virtual void adjust(uint32 _width, uint32 _height);
		virtual void setWindowPos(uint32 x, uint32 y);



	private:

	};

}


#endif