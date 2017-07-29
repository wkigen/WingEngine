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

		virtual uint32 WECFormat2ORFormat(ColorFormat colorType);

		virtual WingEngine::Program* createProgram(std::string name, std::string vs, std::string fs);
		virtual void useProgram(std::string name);

		virtual int32 bindStaticArrayBuffers(uint64 size, void* data);
		virtual int32 bindDynamicArrayBuffers(uint64 size, void* data);
		virtual int32 bindElementBuffers(uint64 size, void* data);
		virtual int32 bindTextureBuffers(ColorFormat colorType, uint32 width, uint32 height, ColorFormat format, void* pixels);

		virtual void bindArrayBuffers(uint32 bufferId);
		virtual void bindElementBuffers(uint32 bufferId);
		virtual void bindTexture(uint32 bufferId);

		virtual void enableDepth(bool enable);
	
		virtual void  enableVertexAttribArray(uint32 location);
		virtual void  disableVertexAttribArray();

		virtual int32 getAttribLocation(int32 programId, std::string name);

		virtual void vertexAttribPointer(uint32 location, uint32 size, bool normalized, uint32 stride, void* pointer);

		virtual int32 getUniformLocation(int32 programId, std::string name);
		virtual void  setUniformMatrix44f(int32 location,int32 count, Matrix44 matrix);

		virtual void render(Renderable* renderables);

	};


}


#endif