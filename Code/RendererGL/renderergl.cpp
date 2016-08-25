#include "renderergl.h"
#include "allocator\allocator.h"
#include "render_context_gl.h"
#include "common\constant.h"

static WingCore::Module* sModule = nullptr;

WingCore::Module* WingDllMain()
{
	sModule = WING_NEW WingCore::Module();
	sModule->mName = "RendererGL";
	sModule->mObject = WING_NEW WingRendererGL::RendererContextGL();
	sModule->mType = ModuleTypeRenderer;
	return sModule;
}