﻿#pragma once
#include "AbstractScreen.h"
#include "Scene.h"

class GameplayScreen
	:public AbstractScreen
{
public:
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	GameplayScreen(GLFWwindow* window);

	void update();
	void render() override;
	void setBackgroundColor() override;

private:
	Scene scene;
	double fps;
	void FPSCounter();
};
