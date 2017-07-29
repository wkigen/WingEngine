#include "renderergl.h"
#include "allocator\allocator.h"
#include "render_context_win_gl.h"
#include "common\constant.h"

static WingEngine::Plugin* sPlugin = nullptr;

WingEngine::Plugin* WingDllMain()
{
	sPlugin = WING_NEW WingEngine::Plugin();
	sPlugin->mName = "RendererGL";
#if WING_PLATFORM_WIN32
	sPlugin->mObject = WING_NEW WingRendererGL::RendererContextWinGL();
#endif
	sPlugin->mType = PluginTypeRenderer;
	return sPlugin;
}