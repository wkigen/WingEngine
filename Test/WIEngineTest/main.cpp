#include <Windows.h>

#include "application\engine_application.h"

class App :public WingEngine::EngineApplication
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


int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, 
	int nCmdShow 
)
{
	WingMain();
}