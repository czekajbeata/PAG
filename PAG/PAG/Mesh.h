#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
class Mesh
{
private:
	unsigned int indices[3] = { 0, 1, 2 };
	float vertices[24] = {
		//pozycja wierzch.	//kolory			//tekstury
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // lewy
		1.0f, -1.0f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,// prawy
		0.0f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f, 0.5f, 1.0f// górny
	};

	// VAO - przechowuje kolejne odwo³ania do atrybutu wierzcho³ka; podczas ich konfigurowania
	// mo¿na je raz ustawiæ a potem przy rysowaniu obiektu podpinaæ do kontekstu odpowiednie VAO - przechowuje ca³y stan

	GLuint VertexBufferObject = NULL;
	GLuint VertexArrayObject = NULL;
	GLuint ElementObjectBuffer = NULL;

public:
	void draw();
	Mesh();
	~Mesh();
};

