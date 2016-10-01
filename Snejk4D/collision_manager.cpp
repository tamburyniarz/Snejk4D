#include "collision_manager.h"
#include <iostream>


CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}

void CollisionManager::ChaeckFood(int foodX, int foodZ)
{
	float head_xpos = 0;
	float head_zpos = 0;
	static bool first = true;

	std::vector<std::queue<glm::vec3>*> position_buffers;

	position_buffers = snake->getPositionBuffers();
	glm::vec3 pos_test;
	pos_test = position_buffers[0]->front();

	head_xpos = pos_test.x;
	head_zpos = pos_test.z;

	if (!(abs(head_xpos - foodX) > 2 || abs(head_zpos - foodZ) > 2))
	{
		std::cout << "Food collision\n";
	}
//	if (!(abs(head_xpos - dizzyX) > 2 || abs(head_zpos - dizzyZ) > 2))


}

bool CollisionManager::CheckTail()
{
	static double lastTime = glfwGetTime();
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	float head_xpos = 0;
	float head_zpos = 0;
	static bool first = true;

	std::vector < std::queue <glm::vec3>* > position_buffers;
	if (first && (deltaTime > 3)) {
		first = false;
		lastTime = currentTime;
	}
	if (!first)
	{
		position_buffers = snake->getPositionBuffers();
		glm::vec3 pos_test;
		pos_test = position_buffers[0]->front();

		head_xpos = pos_test.x;
		head_zpos = pos_test.z;


		for (int i = 15; i < snake->getSize(); ++i)
		{
			glm::vec3 old_pos;
			old_pos = position_buffers[i]->front();
			if (!(abs(head_xpos - old_pos.x) > 2 || abs(head_zpos - old_pos.z) > 2))
				return true;
		}
	}
	return false;
}

void CollisionManager::setSnake(Snake* snake)
{
	this->snake = snake;
}