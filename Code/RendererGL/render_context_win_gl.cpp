#include "render_context_win_gl.h"
#include "log\log.h"

namespace WingRendererGL
{

	RendererContextWinGL::RendererContextWinGL()
	{

	}

	RendererContextWinGL::~RendererContextWinGL()
	{

	}


	bool RendererContextWinGL::create(void* windowHandle, uint32 width, uint32 height)
	{
		RendererContextGL::create(windowHandle, width, height);

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

		if (GLEW_OK != glewInit())
		{
			return false;
		}

		const GLubyte* name = glGetString(GL_VENDOR);				//返回负责当前OpenGL实现厂商的名字  
		const GLubyte* biaoshifu = glGetString(GL_RENDERER);		//返回一个渲染器标识符，通常是个硬件平台  
		const GLubyte* OpenGLVersion = glGetString(GL_VERSION);		//返回当前OpenGL实现的版本号  

		WING_LOG_INFO("the opengl version is %s", OpenGLVersion);

		return true;
	}

	void RendererContextWinGL::swapBuffers()
	{
		::SwapBuffers(mHDC);
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