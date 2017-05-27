#include <Windows.h>
#include "geometry\cube.h"
#include "application\engine_application.h"
#include "scene\scene_system.h"
using namespace WingEngine;

class App :public EngineApplication
{
public:
	virtual bool init()
	{

		Cube* cube = new Cube;
		SceneSystem::getInstance()->addNode("cube",cube);

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