#pragma once
#include "Project1/Scene.h"

class TestScene : public GameEngine::Scene
{
public:
	void onStart() override;
	void onUpdate(double deltaTime) override;
};

