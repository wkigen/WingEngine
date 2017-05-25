#ifndef _WING_RENDERERGL_RENDERER_CONTEXT_GL_H_
#define _WING_RENDERERGL_RENDERER_CONTEXT_GL_H_

#include <GL/glew.h>
#include "GL\wglew.h"
#include "renderer\renderer_context.h"
#include "renderer\renderable.h"

using namespace WingEngine;

namespace WingRendererGL
{

	class RendererContextGL :public WingEngine::RendererContext
	{
	public:
		RendererContextGL();
		virtual ~RendererContextGL();

		virtual bool create(void* windowHandle, uint32 width, uint32 height);
		virtual void destroy()=0;

		virtual void swapBuffers() = 0;

		virtual void clear();

		virtual WingEngine::Program*	createProgram(std::string name, std::string vs, std::string fs);
		virtual void					useProgram(std::string name);
		virtual void					setUniformMatrix44f(std::string name,Matrix44 matrix);

		virtual void render(Renderable* renderables, Matrix44 projectMatrix);

	};


}


#endif