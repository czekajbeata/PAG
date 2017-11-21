#pragma once
#define GLFW_INCLUDE_NONE

#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Scene
{
private:
	glm::mat4 ViewSpace;
	glm::mat4 ProjectionSpace;
public:
	Scene();
	glm::mat4 getViewSpace();
	glm::mat4 getProjectionSpace();
	void updateViewSpace(glm::mat4 pViewSpace);
	void updateSpace(GLuint shader);
	~Scene();
};