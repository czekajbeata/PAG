#include "Mesh.h"

void Mesh::draw()
{
	//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices));
}

Mesh::Mesh()
{
	// generate object array
	glGenVertexArrays(1, &VertexArrayObject);
	// generate object buffer with size 1
	glGenBuffers(1, &VertexBufferObject);
	// generate element buffer with size 1
//	glGenBuffers(1, &ElementObjectBuffer);

	// bind the Vertex Array Object 
	glBindVertexArray(VertexArrayObject);
	// bind and set vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementObjectBuffer);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//configure vertex attributes(s).

	//interpretowanie danych z bufora wierzcho�k�w dla ka�dego atrybutu wierzcho�ka
	// ustawianie wska�nik�w atrybutu wierzcho�ka
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
}


Mesh::~Mesh()
{
}
