#ifndef _WING_ENGINE_RENDERER_CONTEXT_H_
#define _WING_ENGINE_RENDERER_CONTEXT_H_

#include <string>
#include <map>
#include "common\engine_defines.h"
#include "program.h"
#include "camera.h"
#include "shader\shader.h"
#include "renderable.h"
#include "math\matrix44.h"

using namespace WingCore;

namespace WingEngine
{

	class WING_ENGINE_API RendererContext
	{

	public:
		RendererContext();
		virtual ~RendererContext();

		virtual bool		create(void* windowHandle,uint32 width,uint32 height);
		virtual void		destroy() = 0;

		virtual void		swapBuffers() = 0;
		virtual void		clear() = 0;

		virtual void		addProgram(std::string name, Program* program);
		virtual Program*	getProgram(std::string name);

		virtual Program*	createProgram(std::string name, std::string vs, std::string fs)=0;
		virtual void		useProgram(std::string name)=0;

		virtual void		setUniformMatrix44f(std::string name, Matrix44 matrix)=0;

		virtual void		render(Renderable* renderables,Matrix44 projectMatrix) = 0;

	protected:
		std::map<std::string, Program*> mPrograms;
		Program* mCurrProgram;

	};
}


#endif