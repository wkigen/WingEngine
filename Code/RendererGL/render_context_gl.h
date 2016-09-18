#ifndef _WING_RENDERERGL_RENDERER_CONTEXT_GL_H_
#define _WING_RENDERERGL_RENDERER_CONTEXT_GL_H_

#include <GL/glew.h>
#include "renderer\renderer_context.h"

namespace WingRendererGL
{

	class RendererContextGL :public WingEngine::RendererContext
	{
	public:
		RendererContextGL();
		virtual ~RendererContextGL();

		virtual bool create(void* windowHandle)=0;
		virtual void destroy()=0;

		virtual WingEngine::Program*	createProgram(std::string name, std::string vs, std::string fs);
		virtual void					useProgram(std::string name);

		virtual void render();
	};


}


#endif