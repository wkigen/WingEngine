#include <Windows.h>
#include "wing_engine.h"

using namespace WingEngine;

class App :public EngineApplication
{
public:
	virtual bool init()
	{

		SmartPtr<Cube> cube = new Cube();
		cube->setRenderPass(RendererSystem::getInstance()->getRenderPass("GeometryTextureLightPass"));
		SceneSystem::getInstance()->addNode("cube",cube);

		SmartPtr<Plane> plane = new Plane();
		plane->setRenderPass(RendererSystem::getInstance()->getRenderPass("GeometryTextureLightPass"));
		SceneSystem::getInstance()->addNode("plane", plane);

		Image* redImage = ResourceSystem::getInstance()->loadResource<Image>("res/image/red.png");
		Image* whiteImage = ResourceSystem::getInstance()->loadResource<Image>("res/image/white.png");
		Image* image = ResourceSystem::getInstance()->loadResource<Image>("res/image/test.png");

		//---matrial
		SmartPtr<Texture> texture = new Texture(redImage);
		texture->bindGPUBuffer();
		SmartPtr<Material> matrial = new Material();
		matrial->setTexture(texture);
		cube->setMaterial(matrial);

		SmartPtr<Texture> texture2 = new Texture(whiteImage);
		texture2->bindGPUBuffer();
		SmartPtr<Material> matrial2 = new Material();
		matrial2->setTexture(texture2);
		plane->setMaterial(matrial2);

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