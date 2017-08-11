#include "render_context_gl.h"
#include "program_gl.h"
#include "allocator\allocator.h"

namespace WingRendererGL
{

	RendererContextGL::RendererContextGL()
	{
		
	}

	RendererContextGL::~RendererContextGL()
	{

	}

	bool RendererContextGL::create(void* windowHandle, uint32 width, uint32 height)
	{
		RendererContext::create(windowHandle, width, height);

		return false;
	}

	uint32 RendererContextGL::WETType2TType(TextureID textureId)
	{
		switch (textureId)
		{
		case TEXTUREID0:
			return GL_TEXTURE0;
		case TEXTUREID1:
			return GL_TEXTURE1;
		case TEXTUREID2:
			return GL_TEXTURE2;
		case TEXTUREID3:
			return GL_TEXTURE3;
		case TEXTUREID4:
			return GL_TEXTURE4;
		}
	}

	uint32 RendererContextGL::WEDType2DType(DataElementType dataElementType)
	{
		switch (dataElementType)
		{
		case DataElementByte:
			return GL_BYTE;
		case DataElementUByte:
			return GL_UNSIGNED_BYTE;
		case DataElementShort:
			return GL_SHORT;
		case DataElementInt:
			return GL_INT;
		case DataElementUInt:
			return GL_UNSIGNED_INT;
		case DataElementReal:
			return GL_FLOAT;
		default:
			return GL_UNSIGNED_BYTE;
		}
	}

	void RendererContextGL::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	uint32 RendererContextGL::WETFormat2TFormat(TextureFormat textureFormat)
	{
		switch (textureFormat)
		{
		case TextureFormatAlpha:
			return GL_ALPHA;
		case TextureFormatDepth:
			return GL_DEPTH_COMPONENT;
		case TextureFormatLumince:
			return GL_LUMINANCE;
		case TextureFormatLuminceAlpha:
			return GL_LUMINANCE_ALPHA;
		case TextureFormatIntensity:
			return GL_INTENSITY;
		case TextureFormatRGB:
			return GL_RGB;
		case TextureFormatRGBA:
			return GL_RGBA;
		}
	}

	uint32 RendererContextGL::WECFormat2CFormat(ColorFormat colorType)
	{
		switch (colorType)
		{
		case ColorFormatRGBA8:
			return GL_RGBA8;
		case ColorFormatRGB:
			return GL_RGB;
		case ColorFormatRGBA:
			return GL_RGBA;
		case ColorFormatDepth:
			GL_DEPTH_COMPONENT;
		default:
			return GL_RGBA;
		}
	}

	uint32 RendererContextGL::WETFormat2TFormat(TextureType textureType)
	{
		switch (textureType)
		{
		case TextureTypeRGB:
			return GL_RGB;
		case TextureTypeRGBA:
			return GL_RGBA;
		case TextureTypeDepth:
			return GL_DEPTH_COMPONENT;
		default:
			return GL_RGBA;
		}
	}

	uint32 RendererContextGL::WEAPoint2APoint(AttachmentPoint attachmentPoint)
	{
		switch (attachmentPoint)
		{
		case AttachmentPointColor0:
			return GL_COLOR_ATTACHMENT0;
		case AttachmentPointColor1:
			return GL_COLOR_ATTACHMENT1;
		case AttachmentPointColor2:
			return GL_COLOR_ATTACHMENT2;
		case AttachmentPointColor3:
			return GL_COLOR_ATTACHMENT3;
		case AttachmentPointColor4:
			return GL_COLOR_ATTACHMENT4;
		case AttachmentPointColor5:
			return GL_COLOR_ATTACHMENT5;
		case AttachmentPointDepth:
			return GL_DEPTH_ATTACHMENT;
		case AttachmentPointStencil:
			return GL_STENCIL_ATTACHMENT;
		default:
			return GL_COLOR_ATTACHMENT0;
		}
	}

	SmartPtr<Program> RendererContextGL::createProgram(std::string name, std::string vs, std::string fs)
	{
		SmartPtr<Program> program = WING_NEW ProgramGL();	
		program->create(vs, fs);
		return program;
	}

	void RendererContextGL::activityTexture(TextureID textureId)
	{
		glActiveTexture(WETType2TType(textureId));
	}

	int32 RendererContextGL::bindStaticArrayBuffers(uint64 size, void* data)
	{
		GLuint bufferId;
		glGenBuffers(1, &bufferId);
		glBindBuffer(GL_ARRAY_BUFFER, bufferId);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, INVALID_BUFFERS);

		return bufferId;
	}

	int32 RendererContextGL::bindDynamicArrayBuffers(uint64 size, void* data)
	{
		GLuint bufferId;
		glGenBuffers(1, &bufferId);
		glBindBuffer(GL_ARRAY_BUFFER, bufferId);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, INVALID_BUFFERS);

		return bufferId;
	}

	int32 RendererContextGL::bindElementBuffers(uint64 size, void* data)
	{
		GLuint bufferId;
		glGenBuffers(1, &bufferId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, INVALID_BUFFERS);

		return bufferId;
	}

	int32 RendererContextGL::bindTextureBuffers(TextureFormat textureFormat, uint32 width, uint32 height, ColorFormat format, DataElementType dataType, void* pixels)
	{
		unsigned int textureID;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
		glTexImage2D(GL_TEXTURE_2D, 0, WETFormat2TFormat(textureFormat), width, height, 0, WECFormat2CFormat(format), WEDType2DType(dataType), pixels);
		glBindTexture(GL_TEXTURE_2D, INVALID_BUFFERS);
		return textureID;
	}

	int32 RendererContextGL::bindRenderTarget(AttachmentPoint attachmenPoiont, TextureType textureType, uint32 width, uint32 height, uint32 textureId)
	{
		glBindTexture(GL_TEXTURE_2D, textureId);

		//unsigned int rdoID;
		//glGenRenderbuffers(1, &rdoID);
		//glBindRenderbuffer(GL_RENDERBUFFER, rdoID);
		//glRenderbufferStorage(GL_RENDERBUFFER, WETFormat2TFormat(textureType), width, height);
		
		unsigned int fboID;
		glGenFramebuffers(1,&fboID);
		glBindFramebuffer(GL_FRAMEBUFFER, fboID);
		//glFramebufferRenderbuffer(GL_FRAMEBUFFER, WEAPoint2APoint(attachmenPoiont), GL_RENDERBUFFER, rdoID);
		glFramebufferTexture2D(GL_FRAMEBUFFER, WEAPoint2APoint(attachmenPoiont), GL_TEXTURE_2D, textureId,0);

		glBindTexture(GL_TEXTURE_2D, INVALID_BUFFERS);
		//glBindRenderbuffer(GL_RENDERBUFFER, INVALID_BUFFERS);
		glBindFramebuffer(GL_FRAMEBUFFER, INVALID_BUFFERS);

		GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER);
		if (status != GL_FRAMEBUFFER_COMPLETE_EXT)
			return INVALID_BUFFERS;

		return fboID;
	}

	void RendererContextGL::getTextureData(uint32 textureId, ColorFormat format, DataElementType dataType, void* pixels)
	{
		glBindTexture(GL_TEXTURE_2D, textureId);
		glGetTexImage(GL_TEXTURE_2D, 0, WECFormat2CFormat(format), WEDType2DType(dataType), pixels);
		glBindTexture(GL_TEXTURE_2D, INVALID_BUFFERS);
	}

	void RendererContextGL::bindArrayBuffers(uint32 bufferId)
	{
		glBindBuffer(GL_ARRAY_BUFFER, bufferId);
	}

	void RendererContextGL::bindElementBuffers(uint32 bufferId)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
	}

	void RendererContextGL::bindTexture(uint32 bufferId)
	{
		glBindTexture(GL_TEXTURE_2D,bufferId);
	}

	void RendererContextGL::bindRenderTarget(uint32 renderTarget)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, renderTarget);
	}

	void RendererContextGL::enableDepth(bool enable)
	{
		if (enable)
		{
			glEnable(GL_DEPTH_TEST);
		}
		else
		{
			glDisable(GL_DEPTH_TEST);
		}
	}

	void RendererContextGL::enableVertexAttribArray(uint32 location)
	{
		glEnableVertexAttribArray(location);
	}

	void RendererContextGL::disableVertexAttribArray()
	{
		glDisableVertexAttribArray(0);
	}

	int32 RendererContextGL::getAttribLocation(int32 programId, std::string name)
	{
		GLint location = glGetAttribLocation(programId, name.c_str());
		if (location == INVALID_LOCALTION)
		{
			WING_LOG_ERROR("can't no find uniform %s", name.c_str());
		}
		return location;
	}

	void RendererContextGL::vertexAttribPointer(uint32 location, uint32 size, bool normalized, uint32 stride, void* pointer)
	{
		glVertexAttribPointer(location, size, GL_FLOAT, normalized, stride, pointer);
	}

	int32 RendererContextGL::getUniformLocation(int32 programId, std::string name)
	{
		GLint location = glGetUniformLocation(programId, name.c_str());
		if (location == INVALID_LOCALTION)
		{
			WING_LOG_ERROR("can't no find uniform %s", name.c_str());
		}
		return location;
	}

	void RendererContextGL::setUniform1d(int32 location, int32 data)
	{
		glUniform1i(location, data);
	}

	void RendererContextGL::setUniform1dv(int32 location, uint32 count, int32* data)
	{
		glUniform1iv(location, count, data);
	}

	void RendererContextGL::setUniform1f(int32 location, real one)
	{
		glUniform1f(location, one);
	}

	void RendererContextGL::setUniform1fv(int32 location, uint32 count, real* data)
	{
		glUniform1fv(location, count, data);
	}

	void RendererContextGL::setUniform2f(int32 location,  real one, real two)
	{
		glUniform2f(location, one,two);
	}

	void RendererContextGL::setUniform2fv(int32 location, uint32 count, real* data)
	{
		glUniform2fv(location, count, data);
	}

	void RendererContextGL::setUniform3f(int32 location, real one, real two, real three)
	{
		glUniform3f(location, one, two,three);
	}

	void RendererContextGL::setUniform3fv(int32 location, uint32 count, real* data)
	{
		glUniform3fv(location, count, data);
	}

	void RendererContextGL::setUniform3f(int32 location, Vectorf v)
	{
		setUniform3f(location, v.x, v.y, v.z);
	}

	void RendererContextGL::setUniform4f(int32 location, real one, real two, real three, real four)
	{
		glUniform4f(location, one, two,three,four);
	}

	void RendererContextGL::setUniform4fv(int32 location, uint32 count, real* data)
	{
		glUniform4fv(location, count, data);
	}

	void RendererContextGL::setUniformMatrix44f(int32 location, int32 count, real* matrix)
	{
		glUniformMatrix4fv(location, count,false, matrix);
	}

	void RendererContextGL::draw(uint32 count)
	{
		glDrawElements(GL_TRIANGLES, count,GL_UNSIGNED_INT, 0);
	}



}