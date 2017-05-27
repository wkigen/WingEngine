#ifndef _WING_ENGINE_RENDERER_CONTEXT_H_
#define _WING_ENGINE_RENDERER_CONTEXT_H_

#include <string>
#include <map>
#include "common\constant.h"
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

		virtual int32		bindStaticArrayBuffers(uint64 size, void* data) = 0;
		virtual int32		bindDynamicArrayBuffers(uint64 size, void* data) = 0;
		virtual int32		bindElementBuffers(uint64 size, void* data) = 0;

		virtual void		bindArrayBuffers(uint32 bufferId) = 0;
		virtual void		bindElementBuffers(uint32 bufferId) = 0;
		
		virtual void		vertexAttribPointer(uint32 location,uint32 size,bool normalized, uint32 stride, void* pointer) = 0;

		virtual void		enableVertexAttribArray(uint32 location) = 0;
		virtual void		disableVertexAttribArray() = 0;

		virtual int32		getAttribLocation(int32 programId, std::string name) = 0;

		virtual int32		getUniformMatrix44fLocation(int32 programId,std::string name)=0;
		virtual void		setUniformMatrix44f(int32 location, int32 count, Matrix44 matrix) =0;

		virtual void		render(Renderable* renderables) = 0;

	protected:
		std::map<std::string, Program*> mPrograms;
		Program* mCurrProgram;

	};
}


#endif