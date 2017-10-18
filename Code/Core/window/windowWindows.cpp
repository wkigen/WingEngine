#include "windowWindows.h"
#include "math\math.h"
namespace WingCore
{

	long CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
	{
		int fff = 1 + 2;
		switch (message)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_SIZE:
			RECT rc;
			GetClientRect(hwnd, &rc);
			break;
		default:
			break;
		}
		return DefWindowProc(hwnd, message, wParam, lParam);;
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
		WNDCLASS wndcls;											//����һ��wndcls���������  
		wndcls.cbClsExtra = 0;										//�����ռ�õĴ洢�ռ�  
		wndcls.cbWndExtra = 0;										//ʵ������ռ�õĴ洢�ռ�  
		wndcls.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);	//ָ�������໭ˢ���  
		wndcls.hCursor = LoadCursor(NULL, IDC_ARROW);				//ָ������������  
		wndcls.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//ָ��������ͼ����  
		wndcls.hInstance = instance;								//�������ڹ��̵ĳ����ʵ�����  
		wndcls.lpfnWndProc = WndProc;							//ָ�򴰿ڹ��̺���  
		wndcls.lpszClassName = "WingEngine";						//ָ������������  
		wndcls.lpszMenuName = NULL;									//ָ���˵���Դ����  
		wndcls.style = CS_HREDRAW | CS_VREDRAW ;						//ָ������������ʽ  

		RegisterClass(&wndcls);										//ע�ᴰ��

		mHandle = (void*)CreateWindow("WingEngine"
			, "WingEngine"
			, WS_OVERLAPPEDWINDOW
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

		MoveWindow((HWND)mHandle, GetSystemMetrics(SM_CXSCREEN) / 2 - mWidth / 2, GetSystemMetrics(SM_CYSCREEN) / 2 - mHeight / 2, mWidth, mHeight, FALSE);

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