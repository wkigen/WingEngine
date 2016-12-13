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
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		if (vertexbuffer == 0)
		{
			glGenVertexArrays(1, &VertexArrayID);
			glBindVertexArray(VertexArrayID);

			static const GLfloat g_vertex_buffer_data[] = {
				-1.0f, -1.0f, 0.0f,
				1.0f, -1.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
			};


			// Generate 1 buffer, put the resulting identifier in vertexbuffer
			glGenBuffers(1, &vertexbuffer);

			// The following commands will talk about our 'vertexbuffer' buffer
			glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

			// Give our vertices to OpenGL.
			glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
		}


		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle

		glDisableVertexAttribArray(0);
	}

}