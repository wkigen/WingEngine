#include "renderer_context.h"
#include "log\log.h"
#include "allocator\allocator.h"

namespace WingEngine
{
	RendererContext::RendererContext()
	{
		Point<float> eye(0,0,-1);
		Point<float> at(0, 0, 0);
		Vector<float> up(0, 1, 0);
		mMainCamera = WING_NEW Camera(eye,at,up);
	}

	RendererContext::~RendererContext()
	{

	}

	void RendererContext::addProgram(std::string name, Program* program)
	{
		if (mPrograms.find(name) != mPrograms.end())
		{
			WING_LOG_WARN("is has same name [%s] in programs list", name.c_str());
			return;
		}
		mPrograms[name] = program;
	}

	Program* RendererContext::getProgram(std::string name)
	{
		std::map<std::string, Program*>::iterator itor = mPrograms.find(name);
		if (itor != mPrograms.end())
		{
			return itor->second;
		}
		WING_LOG_ERROR("can't find [%s] program in programs list", name.c_str());
		return nullptr;
	}
}