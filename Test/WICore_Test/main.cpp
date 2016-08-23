

#include "log\log.h"
#include "dll\dll_system.h"
#include "config\config.h"
#include "window\windowWindows.h"
#include "application\application.h"
#include "application\main.h"


class App :public WingCore::Application
{
public:
	virtual bool init() 
	{
		return true;
	}

	virtual void clear()
	{

	}

};

WING_MAIN(App);


int main()
{

	WingCore::WING_LOG_INFO("Wing Engine test");


	//WingCore::DllSystem::getInstance()->open("D:/github/Wing/Bin/Runtime/X86/WIRendererD.dll");
	//WingCore::DllSystem::getInstance()->close("Renderer");


	WingCore::Config* config = WING_NEW WingCore::Config();
	config->setAttribute("11111", "1", "string");
	config->setAttribute("11111", "2", 200);
	std::string value1;
	config->getAttrbute("11111", "1", value1);
	real value2;
	config->getAttrbute("11111", "2", value2);
	WING_DELETE(config);

	/*
	WingCore::WindowWindows* window = WING_NEW WingCore::WindowWindows();
	window->init();
	WING_DELETE(window);
	*/

	WingMain();

	return 0;
}