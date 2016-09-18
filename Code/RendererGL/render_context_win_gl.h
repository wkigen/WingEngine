#ifndef _WING_RENDERERGL_RENDERER_CONTEXT_GL_WIN_H_
#define _WING_RENDERERGL_RENDERER_CONTEXT_GL_WIN_H_

#include "GL\wglew.h"
#include "render_context_gl.h"

namespace WingRendererGL
{

	class RendererContextWinGL :public WingRendererGL::RendererContextGL
	{
	public:
		RendererContextWinGL();
		virtual ~RendererContextWinGL();

		virtual bool create(void* windowHandle);
		virtual void destroy();

	private:
		HWND	mHwnd;
		HGLRC	mHRC;
		HDC		mHDC;
	};


}


#endif