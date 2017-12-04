#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Material
{
private:

public:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;

	Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess);
	
	~Material();
}; 
