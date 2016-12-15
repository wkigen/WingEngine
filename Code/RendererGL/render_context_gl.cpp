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

	void RendererContextGL::setUniformMatrix44f(std::string name, Matrix44 matrix)
	{
		GLuint location =  glGetUniformLocation(mCurrProgram->getProgramID(), name.c_str());
		if (location == -1)
		{
			WING_LOG_ERROR("can't no find uniform %s",name.c_str());
			return;
		}

		glUniformMatrix4fv(location, 1, 1, matrix.mData.data);
	}

	void RendererContextGL::render()
	{
		Vector<float> tra(0.01, 0, 0);
		mMainCamera->translation(tra);

		setUniformMatrix44f(PROJECTMODELVIEWMARTIX, mMainCamera->getProjectModelMatrix44());

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBegin(GL_TRIANGLES);
		glVertex3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glEnd();

		swapBuffers();
	}

}