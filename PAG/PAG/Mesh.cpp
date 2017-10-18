#include "Mesh.h"

void Mesh::draw()
{
	glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices));
}

Mesh::Mesh()
{
	// generate object array
	// VAO - przechowuje kolejne odwo³ania do atrybutu wierzcho³ka; podczas ich konfigurowania
	// mo¿na je raz ustawiæ a potem przy rysowaniu obiektu podpinaæ do kontekstu odpowiednie VAO - przechowuje ca³y stan
	glGenVertexArrays(1, &VertexArrayObject);
	// bind the Vertex Array Object 
	glBindVertexArray(VertexArrayObject);
	
	// generate object buffer with size 1
	glGenBuffers(1, &VertexBufferObject);
	// bind and set vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// generate element buffer with size 1
	glGenBuffers(1, &ElementObjectBuffer);
	// bind and set Element Object Buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementObjectBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//configure vertex attributes(s).

	//interpretowanie danych z bufora dla ka¿dego atrybutu wierzcho³ka
	// ustawianie wskaŸników atrybutu wierzcho³ka

	// Atrybut pozycji
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Atrybut koloru
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Atrybut koordynacji tekstury
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
}


Mesh::~Mesh()
{
}
