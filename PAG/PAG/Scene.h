#pragma once
#define GLFW_INCLUDE_NONE

#include <stdio.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "Const.h"
#include "Camera.h"

class Shader;

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