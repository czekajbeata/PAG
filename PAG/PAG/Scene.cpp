#include "Scene.h"
#include "Shader.h"
#include <glm/gtc/matrix_transform.hpp>

Scene::Scene()
{
	ProjectionSpace = glm::perspective(45.0f, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.001f, 50.0f); //FOV, Aspect Ratio, zNear, zFar
}

glm::mat4 Scene::getViewSpace() { return ViewSpace; }
glm::mat4 Scene::getProjectionSpace() { return ProjectionSpace; }

void Scene::updateViewSpace(glm::mat4 pViewSpace) 
{
	ViewSpace = pViewSpace; 
}

void Scene::updateSpace(GLuint shader)
{
	GLint projLoc = glGetUniformLocation(shader, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(ProjectionSpace));

	GLint viewLoc = glGetUniformLocation(shader, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(ViewSpace));
}

Scene::~Scene() {}