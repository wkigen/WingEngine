#ifndef _WING_RENDERERGL_PROGRAM_GL_H_
#define _WING_RENDERERGL_PROGRAM_GL_H_

#include <GL/glew.h>
#include "renderer\program.h"

namespace WingRendererGL
{

	class ProgramGL : public WingEngine::Program
	{

	public:
		ProgramGL();
		~ProgramGL();

		virtual void create(std::string vs, std::string fs);
		virtual void use();
		virtual void destroy();

	private:
	

	};
}


#endif