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
		virtual void destroy() = 0;

		virtual void swapBuffers() = 0;

		virtual void clear();

		virtual uint32 WETType2TType(TextureID textureId);
		virtual uint32 WEDType2DType(DataElementType dataElementType);
		virtual uint32 WETFormat2TFormat(TextureFormat textureFormat);
		virtual uint32 WECFormat2CFormat(ColorFormat colorType);
		virtual uint32 WETFormat2TFormat(TextureType textureType);
		virtual uint32 WEAPoint2APoint(AttachmentPoint attachmentPoint);

		virtual SmartPtr<Program> createProgram(std::string name, std::string vs, std::string fs);

		virtual void activityTexture(TextureID textureId);

		virtual void bingSubDataBuffer(uint32 bufferId, uint64 size, void* data);
		virtual int32 bindStaticArrayBuffers(uint64 size, void* data);
		virtual int32 bindDynamicArrayBuffers(uint64 size, void* data);
		virtual int32 bindElementBuffers(uint64 size, void* data);
		virtual int32 bindTextureBuffers(TextureFormat textureFormat,uint32 width, uint32 height, ColorFormat format, DataElementType dataType, void* pixels);
		virtual int32 bindRenderTarget(AttachmentPoint attachmenPoiont, TextureType textureType, uint32 width, uint32 height, uint32 textureId);
		virtual void getTextureData(uint32 textureId, ColorFormat format, DataElementType dataType, void* pixels);

		virtual void bindArrayBuffers(uint32 bufferId);
		virtual void bindElementBuffers(uint32 bufferId);
		virtual void bindTexture(uint32 bufferId);
		virtual void deleteTexture(uint32 bufferId);
		virtual void bindRenderTarget(uint32 renderTarget);

		virtual void enableDepth(bool enable);
	
		virtual void  enableVertexAttribArray(uint32 location);
		virtual void  disableVertexAttribArray();

		virtual int32 getAttribLocation(int32 programId, std::string name);

		virtual void vertexAttribPointer(uint32 location, uint32 size, bool normalized, uint32 stride, void* pointer);

		virtual int32 getUniformLocation(int32 programId, std::string name);

		virtual void  setUniform1d(int32 location, int32 data);
		virtual void  setUniform1dv(int32 location, uint32 count, int32* data);
		virtual void  setUniform1f(int32 location, real one);
		virtual void  setUniform1fv(int32 location,uint32 count , real* data);

		virtual void  setUniform2f(int32 location, real one, real two);
		virtual void  setUniform2fv(int32 location, uint32 count, real* data);

		virtual void  setUniform3f(int32 location, real one, real two, real three);
		virtual void  setUniform3fv(int32 location, uint32 count, real* data);
		virtual void  setUniform3f(int32 location, Vectorf v);

		virtual void  setUniform4f(int32 location, real one, real two, real three, real four);
		virtual void  setUniform4fv(int32 location, uint32 count, real* data);

		virtual void  setUniformMatrix44f(int32 location,int32 count, real* matrix);

		virtual void  draw(uint32 count);

	};


}


#endif