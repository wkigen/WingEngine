#include <Windows.h>
#include "wing_engine.h"

using namespace WingEngine;

class App :public EngineApplication
{
public:
	virtual bool init()
	{

		Cube* cube = new Cube;
		SceneSystem::getInstance()->addNode("cube",cube);

		ResourceSystem::getInstance()->loadResource<Image>("res/image/test.png");
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