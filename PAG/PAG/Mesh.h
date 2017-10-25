#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
class Mesh
{
private:
	unsigned int indices[6] = { 0, 1, 2, 
							   1, 2, 3 };
	float vertices[32] = {
		//pozycje wierzholkow	//kolory			//tekstury
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	1.0f, 1.0f,		// lewy
		0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f,		// prawy
		-0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	1.0f, 0.0f,		// górny lewy
		0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 0.0f		// górny prawy

	};

	GLuint VertexBufferObject = NULL;
	GLuint VertexArrayObject = NULL;
	GLuint ElementObjectBuffer = NULL;

public:
	void draw();
	Mesh();
	~Mesh();
};

