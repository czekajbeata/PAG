#pragma once
#include <glad/glad.h>
class Mesh
{
private:
//	unsigned int indices[3] = { 0, 1, 3 };
	float vertices[9] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	// VAO - przechowuje kolejne odwo³ania do atrybutu wierzcho³ka; podczas ich konfigurowania
	// mo¿na je raz ustawiæ a potem przy rysowaniu obiektu podpinaæ do kontekstu odpowiednie VAO - przechowuje ca³y stan

	GLuint VertexBufferObject = NULL;
	GLuint VertexArrayObject = NULL;
//	GLuint ElementObjectBuffer = NULL;

public:
	void draw();
	Mesh();
	~Mesh();
};

