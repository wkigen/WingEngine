#include "windowWindows.h"
#include "math\math.h"
namespace WingCore
{

	long CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
	{
		switch (message)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
		default:
			return DefWindowProc(hwnd, message, wParam, lParam);
		}
		return (0);
	}

	WindowWindows::WindowWindows()
	{

	}

	WindowWindows::~WindowWindows()
	{

	}

	bool WindowWindows::init()
	{
		HINSTANCE instance = (HINSTANCE)GetModuleHandle(NULL);
		WNDCLASS wndcls;											//定义一个wndcls窗口类对象  
		wndcls.cbClsExtra = 0;										//类变量占用的存储空间  
		wndcls.cbWndExtra = 0;										//实例变量占用的存储空间  
		wndcls.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);	//指定窗口类画刷句柄  
		wndcls.hCursor = LoadCursor(NULL, IDC_ARROW);				//指定窗口类光标句柄  
		wndcls.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//指定窗口类图标句柄  
		wndcls.hInstance = instance;								//包含窗口过程的程序的实例句柄  
		wndcls.lpfnWndProc = WndProc;							//指向窗口过程函数  
		wndcls.lpszClassName = "WingEngine";						//指定窗口类名字  
		wndcls.lpszMenuName = NULL;									//指定菜单资源名字  
		wndcls.style = CS_HREDRAW | CS_VREDRAW;						//指定窗口类型样式  

		RegisterClass(&wndcls);										//注册窗口

		mHandle = (void*)CreateWindow("WingEngine"
			, "WingEngine"
			, WS_OVERLAPPEDWINDOW | WS_VISIBLE
			, 0
			, 0
			, mWidth
			, mHeight
			, NULL
			, NULL
			, instance
			, 0
		);

		adjust(mWidth,mHeight);

		return true;
	}

	void WindowWindows::adjust(uint32 _width, uint32 _height)
	{
		mWidth = _width;
		mHeight = _height;
		real aspectRatio = real(_width) / real(_height);
		ShowWindow((HWND)mHandle, SW_SHOWNORMAL);

		RECT rect;
		RECT newrect = { 0, 0, (LONG)_width, (LONG)_height };
		DWORD style = GetWindowLong((HWND)mHandle, GWL_STYLE);

		GetWindowRect((HWND)mHandle, &rect);

		SetWindowLong((HWND)mHandle, GWL_STYLE, style);
		AdjustWindowRect(&newrect, style, FALSE);
		UpdateWindow((HWND)mHandle);

		int32 left = rect.left;
		int32 top = rect.top;
		int32 width = (newrect.right - newrect.left);
		int32 height = (newrect.bottom - newrect.top);
		
		SetWindowPos((HWND)mHandle
			, HWND_TOP
			, left
			, top
			, width
			, height
			, SWP_SHOWWINDOW
		);
		
		ShowWindow((HWND)mHandle, SW_RESTORE);
	}

	void WindowWindows::setWindowPos(uint32 x, uint32 y)
	{
		SetWindowPos((HWND)mHandle, 0, x, y, 0, 0, SWP_NOSIZE);
	}

	void WindowWindows::destriy()
	{
		DestroyWindow((HWND)mHandle);
	}

}