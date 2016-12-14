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
			program->use();
		}
	}

	void RendererContextGL::render()
	{
		Vector<float> tra(0, 0, -0.01);
		mMainCamera->translation(tra);

		glLoadIdentity();
		glTranslatef(0.0, 0.0, -1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBegin(GL_TRIANGLES);
		glVertex3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glEnd();

		swapBuffers();
	}

}