#include "game.h"
#include <cstdio>
#include <ostream>
#include <iostream>
#include "MainMenuScreen.h"
#include "MenuTextButton.h"
#include "FileService.h"
#include "ScreenService.h"

GameStateEnum Game::game_state_enum = MENU;

int Game::Initialize()
{
	if (initGLFW() == -1)
		return -1;
	if (initGLFWwindow() == -1)
		return -1;
	return 0;
}


void Game::update()
{
	ScreenService::getInstance()->getActualScreen()->render();
}

void Game::render()
{
	ScreenService::getInstance()->setScreen(window,ScreenEnum::MAiN_MENU);
	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	do
	{
		// Dark blue background
		glClearColor(0.9f, 0.5f, 1.0f, 0.0f);
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		update();

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	} // Check if the ESC key was pressed or the window_ was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);


	// Close OpenGL window_ and terminate GLFW
	glfwTerminate();
}

int Game::initGLFW()
{
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}
	return 0;
}

int Game::initGLFWwindow()
{
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 
	// Open a window_ and create its OpenGL context
	window = glfwCreateWindow(WIDTH, HEIGHT, "Snejk 4D", NULL, NULL);
	if (window == NULL)
	{
		fprintf(stderr, "Failed to open GLFW window_. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); // Initialize GLEW
	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Set the mouse at the center of the screen
	glfwPollEvents();
	glfwSetCursorPos(window, 1024 / 2, 768 / 2);

	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	return 0;
}
