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
		glEnable(GL_DEPTH_TEST);

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

	int32 RendererContextGL::getUniformMatrix44f(int32 programId, std::string name)
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

	void RendererContextGL::render(Renderable* renderables,Matrix44 projectMatrix)
	{
		int32 location = getUniformMatrix44f(mCurrProgram->getProgramID(), PROJECTMODELVIEWMARTIX);
		setUniformMatrix44f(location,1, projectMatrix);

		glBegin(GL_TRIANGLES);
		glVertex3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, 0.0f);
		glEnd();


	}

}