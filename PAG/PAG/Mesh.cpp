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
}


Mesh::~Mesh()
{
}
