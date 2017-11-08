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

	//float vertices[108] = {
	//	-0.5f, -0.5f, -0.5f,  
	//	0.5f, -0.5f, -0.5f,  
	//	0.5f,  0.5f, -0.5f,  
	//	0.5f,  0.5f, -0.5f,  
	//	-0.5f,  0.5f, -0.5f, 
	//	-0.5f, -0.5f, -0.5f,  

	//	-0.5f, -0.5f,  0.5f,  
	//	0.5f, -0.5f,  0.5f,  
	//	0.5f,  0.5f,  0.5f,  
	//	0.5f,  0.5f,  0.5f,  
	//	-0.5f,  0.5f,  0.5f, 
	//	-0.5f, -0.5f,  0.5f, 

	//	-0.5f,  0.5f,  0.5f, 
	//	-0.5f,  0.5f, -0.5f, 
	//	-0.5f, -0.5f, -0.5f, 
	//	-0.5f, -0.5f, -0.5f, 
	//	-0.5f, -0.5f,  0.5f, 
	//	-0.5f,  0.5f,  0.5f, 

	//	0.5f,  0.5f,  0.5f,  
	//	0.5f,  0.5f, -0.5f,  
	//	0.5f, -0.5f, -0.5f,  
	//	0.5f, -0.5f, -0.5f,  
	//	0.5f, -0.5f,  0.5f,  
	//	0.5f,  0.5f,  0.5f,  

	//	-0.5f, -0.5f, -0.5f, 
	//	0.5f, -0.5f, -0.5f, 
	//	0.5f, -0.5f,  0.5f, 
	//	0.5f, -0.5f,  0.5f, 
	//	-0.5f, -0.5f,  0.5f,
	//	-0.5f, -0.5f, -0.5f,

	//	-0.5f,  0.5f, -0.5f,
	//	0.5f,  0.5f, -0.5f, 
	//	0.5f,  0.5f,  0.5f, 
	//	0.5f,  0.5f,  0.5f, 
	//	-0.5f,  0.5f,  0.5f,
	//	-0.5f,  0.5f, -0.5f
	//};

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


	glm::mat4 WVP;
};

