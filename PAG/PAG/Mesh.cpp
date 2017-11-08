#include "Mesh.h"

void Mesh::draw()
{
	glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices)/5.0f);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

Mesh::Mesh()
{
	glGenVertexArrays(1, &VertexArrayObject);
	// generate object buffer with size 1
	glGenBuffers(1, &VertexBufferObject);
	// bind and set vertex buffers
	glBindVertexArray(VertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//interpretowanie danych z bufora dla ka¿dego atrybutu wierzcho³ka
	// ustawianie wskaŸników atrybutu wierzcho³ka

	// Atrybut pozycji
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	//macierz modelu
	//Model = glm::rotate(Model, glm::radians(135.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	/* Set world matrix to identity matrix - 1 na przek¹tnej*/
	//World = glm::mat4(1.0f);

	/* Set view matrix */
	View = glm::lookAt(glm::vec3(0.0f, 0.0f, -13.0f),  // camera position in world space
						glm::vec3(0.0f, 0.0f, 0.0f),  // point that camera is looking at
						glm::vec3(0.0f, 1.0f, 0.0f)); // head is up / (0,-1,0) upside down

	/* Set projection matrix  - bli¿ej czy dalej*/
	Projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 50.0f);

	/* Set MVP matrix */
	//WVP = Projection * View * World;
}


Mesh::~Mesh()
{
}
