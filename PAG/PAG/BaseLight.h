#pragma once
#define GLFW_INCLUDE_NONE

#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class BaseLight
{
private:

public:
	BaseLight();
	~BaseLight();
};