#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Const.h"

class Mesh
{
private:
	unsigned int indices[6] = { 0, 1, 2, 
							   1, 2, 3 };
	//float vertices[32] = {
	//	//pozycje wierzholkow	//kolory			//tekstury
	//	-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	1.0f, 1.0f,		// lewy
	//	0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f,		// prawy
	//	-0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	1.0f, 0.0f,		// górny lewy
	//	0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 0.0f		// górny prawy

	//};

	glm::vec3 vertices[18] = { 
		glm::vec3(-0.5f, -0.5f,  0.5f), //basis
		glm::vec3(0.5f, -0.5f,  0.5f),
		glm::vec3(0.5f, -0.5f, -0.5f),
		glm::vec3(-0.5f, -0.5f,  0.5f),
		glm::vec3(0.5f, -0.5f, -0.5f),
		glm::vec3(-0.5f, -0.5f, -0.5f),
		
		glm::vec3(-0.5f, -0.5f, -0.5f), //left side
		glm::vec3(-0.5f, -0.5f,  0.5f),
		glm::vec3(0.0f,  0.5f,  0.0f),
		
		glm::vec3(0.5f, -0.5f,  0.5f), //right side
		glm::vec3(0.5f, -0.5f, -0.5f),
		glm::vec3(0.0f,  0.5f,  0.0f),
		
		glm::vec3(-0.5f, -0.5f,  0.5f), //front side
		glm::vec3(0.5f, -0.5f,  0.5f),
		glm::vec3(0.0f,  0.5f,  0.0f),
		
		glm::vec3(0.5f, -0.5f, -0.5f), //back side
		glm::vec3(-0.5f, -0.5f, -0.5f),
		glm::vec3(0.0f,  0.5f,  0.0f) };

	
	GLuint VertexBufferObject = NULL;
	//GLuint VertexArrayObject = NULL;
	//GLuint ElementObjectBuffer = NULL;

public:
	void draw();
	Mesh();
	~Mesh();


	glm::mat4 World;
	glm::mat4 View;
	glm::mat4 Projection;
	glm::mat4 Model;

	// world space positions of our cubes
	glm::vec3 cubePositions[10] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	glm::mat4 WVP;
};

