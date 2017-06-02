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

	void RendererContextGL::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	WingEngine::Program* RendererContextGL::createProgram(std::string name, std::string vs, std::string fs)
	{
		ProgramGL* program = WING_NEW ProgramGL();
		program->create(vs, fs);
		addProgram(name, program);

		return program;
	}

	void RendererContextGL::useProgram(std::string name)
	{
		WingEngine::Program* program  = getProgram(name);
		if (program != nullptr)
		{
			mCurrProgram = program;
			mCurrProgram->use();
		}
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

	void RendererContextGL::bindArrayBuffers(uint32 bufferId)
	{
		glBindBuffer(GL_ARRAY_BUFFER, bufferId);
	}

	void RendererContextGL::bindElementBuffers(uint32 bufferId)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
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

	int32 RendererContextGL::getUniformMatrix44fLocation(int32 programId, std::string name)
	{
		GLint location = glGetUniformLocation(programId, name.c_str());
		if (location == INVALID_LOCALTION)
		{
			WING_LOG_ERROR("can't no find uniform %s", name.c_str());
		}
		return location;
	}

	void RendererContextGL::setUniformMatrix44f(int32 location, int32 count, Matrix44 matrix)
	{
		glUniformMatrix4fv(location, count,false, matrix.mData.data);
	}

	void RendererContextGL::render(Renderable* renderable)
	{
		renderable->getRenderPass()->bind(renderable);

		glBindBuffer(GL_ARRAY_BUFFER, renderable->getVertixData().getGPUBufferId());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderable->getIndeiceData().getGPUBufferId());
		
		glDrawElements(GL_TRIANGLES, renderable->getIndeiceData().getDataNum(),GL_UNSIGNED_INT, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		renderable->getRenderPass()->unBind();
	}

}