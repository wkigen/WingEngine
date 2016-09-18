#include "render_context_win_gl.h"

namespace WingRendererGL
{

	RendererContextWinGL::RendererContextWinGL()
	{

	}

	RendererContextWinGL::~RendererContextWinGL()
	{

	}


	bool RendererContextWinGL::create(void* windowHandle)
	{

		mHwnd = (HWND)windowHandle;
		mHDC = GetDC(mHwnd);

		PIXELFORMATDESCRIPTOR pfd =
		{
			sizeof(PIXELFORMATDESCRIPTOR),  // size
			1,                          // version
			PFD_SUPPORT_OPENGL |        // OpenGL window
			PFD_DRAW_TO_WINDOW |        // render to window
			PFD_DOUBLEBUFFER,           // support double-buffering
			PFD_TYPE_RGBA,              // color type
			32,                         // preferred color depth
			0, 0, 0, 0, 0, 0,           // color bits (ignored)
			0,                          // no alpha buffer
			0,                          // alpha bits (ignored)
			0,                          // no accumulation buffer
			0, 0, 0, 0,                 // accum bits (ignored)
			24,                         // depth buffer
			8,                          // no stencil buffer
			0,                          // no auxiliary buffers
			PFD_MAIN_PLANE,             // main layer
			0,                          // reserved
			0, 0, 0,                    // no layer, visible, damage masks
		};

		int pixelFormat = ChoosePixelFormat(mHDC, &pfd);
		SetPixelFormat(mHDC, pixelFormat, &pfd);

		mHRC = wglCreateContext(mHDC);
		wglMakeCurrent(mHDC, mHRC);

		GLenum GlewInitResult = glewInit();

		return true;
	}

	void RendererContextWinGL::destroy()
	{
		if (mHDC != NULL && mHRC != NULL)
		{
			wglMakeCurrent(mHDC, NULL);
			wglDeleteContext(mHRC);
		}
	}

}