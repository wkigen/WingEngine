#ifndef _WING_ENGINE_RENDERER_CONTEXT_H_
#define _WING_ENGINE_RENDERER_CONTEXT_H_

#include <string>
#include <map>
#include "common\engine_defines.h"
#include "program.h"

namespace WingEngine
{

	class WING_ENGINE_API RendererContext
	{

	public:
		RendererContext() {};
		virtual ~RendererContext() {};

		virtual bool		create(void* windowHandle) = 0;
		virtual void		swapBuffers() = 0;
		virtual void		destroy() = 0;

		virtual void		addProgram(std::string name, Program* program);
		virtual Program*	getProgram(std::string name);
		virtual Program*	createProgram(std::string name, std::string vs, std::string fs)=0;
		virtual void		useProgram(std::string name)=0;

		virtual void		render() = 0;


	private:
		std::map<std::string, Program*> mPrograms;

	};
}


#endif