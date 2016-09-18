#include "renderergl.h"
#include "allocator\allocator.h"
#include "render_context_win_gl.h"
#include "common\constant.h"

static WingCore::Module* sModule = nullptr;

WingCore::Module* WingDllMain()
{
	sModule = WING_NEW WingCore::Module();
	sModule->mName = "RendererGL";
#if WING_PLATFORM_WIN32
	sModule->mObject = WING_NEW WingRendererGL::RendererContextWinGL();
#endif
	sModule->mType = ModuleTypeRenderer;
	return sModule;
}