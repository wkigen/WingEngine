#include <Windows.h>
#include "wing_engine.h"

using namespace WingEngine;

class App :public EngineApplication
{
public:
	virtual bool init()
	{

		SmartPtr<Cube> cube = new Cube();
		cube->setRenderPass(RendererSystem::getInstance()->getRenderPass("GeometryTexturePass"));
		SceneSystem::getInstance()->addNode("cube",cube);

		ResourceSystem::getInstance()->loadResource<Image>("res/image/test.png");

		Image* testImage = ResourceSystem::getInstance()->getResource<Image>("res/image/test.png");

		//---matrial
		SmartPtr<Texture> texture = new Texture(testImage);
		texture->bindGPUBuffer();
		SmartPtr<Material> matrial = new Material();
		matrial->setTexture(texture);
		cube->setMaterial(matrial);

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