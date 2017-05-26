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

		virtual WingEngine::Program* createProgram(std::string name, std::string vs, std::string fs);
		virtual void useProgram(std::string name);

		virtual int32 bindStaticArrayBuffers(uint64 size, void* data);
		virtual int32 bindDynamicArrayBuffers(uint64 size, void* data);
		virtual int32 bindElementBuffers(uint64 size, void* data);
	
		virtual int32 getUniformMatrix44f(int32 programId, std::string name);
		virtual void setUniformMatrix44f(int32 location,int32 count, Matrix44 matrix);

		virtual void render(Renderable* renderables, Matrix44 projectMatrix);

	};


}


#endif