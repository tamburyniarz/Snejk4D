﻿#include "MenuTextButton.h"
#include "FileService.h"

MenuTextButton::MenuTextButton(char* path)
{
	// Create and compile our GLSL program from the shaders
	programID = FileService::LoadShaders("shaders/MenuTextVertexShader.vertexshader", "shaders/MenuTextFragmentShader.fragmentshader");

	Texture = FileService::LoadBMP(path);
	// Get a handle for our "myTextureSampler" uniform
	TextureID = glGetUniformLocation(programID, "myTextureSampler");

	// Get a handle for our "MVP" uniform
	MatrixID = glGetUniformLocation(programID, "MVP");
	float width = 330.0f / 660.0f;
	float height = 51.0f / 660.0f;

	// An array of 3 vectors which represents 3 vertices
	static const GLfloat scene_points[] = {
		-width, -height, 0.0f,
		width, -height, 0.0f,
		width, height, 0.0f,

		width, height, 0.0f,
		-width, height, 0.0f,
		-width, -height, 0.0f,
	};

	GLfloat tex_coords[] = {
		0.0f, 0.0f, // A
		1.0f, 0.0f, // B
		1.0f, 1.0f, // C
		1.0f, 1.0f, // D
		0.0f, 1.0f, // E
		0.0f, 0.0f, // F
	};

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(scene_points), scene_points, GL_STATIC_DRAW);

	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tex_coords), tex_coords, GL_STATIC_DRAW);
}

MenuTextButton::~MenuTextButton()
{
	// Cleanup VBO and shader
	glDeleteProgram(programID);
	glDeleteTextures(1, &TextureID);
}

void MenuTextButton::Display(glm::vec3 pos)
{
	// Use our shader
	glUseProgram(programID);

	glm::mat4 test = glm::translate(glm::mat4(1.0), pos);
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &test[0][0]);

	//// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);
	//// Set our "myTextureSampler" sampler to user Texture Unit 0
	glUniform1i(TextureID, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
