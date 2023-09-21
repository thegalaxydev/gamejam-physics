#include "Project1/Engine.h"
#include "TestScene.h"


int main()
{
	GameEngine::Engine engine = GameEngine::Engine();

	TestScene* testScene = new TestScene();

	engine.setCurrentScene(testScene);

	engine.run();

	return 0;
}