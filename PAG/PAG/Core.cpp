#include <stdio.h>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "Core.h"
#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"
#include "Scene.h"
#include <stdexcept>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

void Core::run()
{
	//glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	Transform center = Transform();
	Transform planet1 = Transform();
	Transform planet1Moon = Transform();

	while (!glfwWindowShouldClose(window->getWindow()))
	{
		glClearColor(BACKGROUND_COLOR);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindVertexArray(mesh->VertexArrayObject);

		GLfloat currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		processInput();
		processMouse();

		scene->updateViewSpace(*camera);
		shader->updateScene(*scene);

		shader->use();

		// TO DO: rotates with the smaller cube
		glm::vec3 lightPosition = glm::vec3(0.0f, 1.0f, 0.0f);
		shader->setVec3("lightPosition", lightPosition);

		planet1.setParent(center);
		planet1.setTransform(center.getTransform());
		//planet1.translate(glm::vec3(2.0f, 0.0f, 0.0f));
		//planet1.rotate(glm::radians(180.0f) * currentTime, glm::vec3(0.0f, 1.0f, 0.0f));
		shader->setMat4("model", planet1.getTransform());
		texture->setActiveTexture(1);
		mesh->draw();

		//light source
		planet1Moon.setParent(planet1);
		planet1Moon.setTransform(planet1.getTransform());
		planet1Moon.rotate(glm::radians(180.0f) * currentTime, glm::vec3(0.0f, 1.0f, 0.0f));
		planet1Moon.translate(glm::vec3(1.5f, 0.0f, 0.0f));
		planet1Moon.scale(glm::vec3(0.5f, 0.5f, 0.5f));
		shader->setMat4("model", planet1Moon.getTransform());
		texture->setActiveTexture(2);
		mesh->draw();


		glfwSwapBuffers(window->getWindow());
		glfwPollEvents();
	}
}



Core::Core()
{
	// glfw: initialize and configure
	if (!glfwInit())
		throw runtime_error("Cannot initialize GLFW");

	window = std::make_unique<Window>();

	// glad: load all OpenGL function pointers
	if (!gladLoadGL())
		throw runtime_error("Cannot initialize GLAD");

	glEnable(GL_DEPTH_TEST);

	mesh = std::make_unique<Mesh>();
	mesh->loadContent();

	texture = std::make_unique<Texture>();

	shader = std::make_unique<Shader>();

	shader->use();
	shader->setInt("texture", 0);

	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	shader->setVec3("lightColor", lightColor);
	float ambientStrength = 0.1;
	glm::vec3 ambient = ambientStrength * lightColor;
	shader->setVec3("ambient", ambient);



	

	camera = std::make_unique<Camera>();
	glfwGetCursorPos(window->getWindow(), &camera->lastX, &camera->lastY);

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	scene = std::make_unique<Scene>();
}

Core::~Core()
{
}

void Core::processInput()
{
	if (glfwGetKey(window->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window->getWindow(), true);

	GLfloat speed = deltaTime * cameraSpeed;
	if (glfwGetKey(window->getWindow(), GLFW_KEY_W) == GLFW_PRESS)
		camera->cameraPos += speed * camera->cameraFront;
	if (glfwGetKey(window->getWindow(), GLFW_KEY_S) == GLFW_PRESS)
		camera->cameraPos -= speed * camera->cameraFront;
	if (glfwGetKey(window->getWindow(), GLFW_KEY_A) == GLFW_PRESS)
		camera->cameraPos -= glm::normalize(glm::cross(camera->cameraFront, camera->cameraUp)) * speed;
	if (glfwGetKey(window->getWindow(), GLFW_KEY_D) == GLFW_PRESS)
		camera->cameraPos += glm::normalize(glm::cross(camera->cameraFront, camera->cameraUp)) * speed;
}

void Core::processMouse()
{

	double mousePosX, mousePosY;
	glfwGetCursorPos(window->getWindow(), &mousePosX, &mousePosY);

	if (camera->firstMouse)
	{
		camera->lastX = mousePosX;
		camera->lastY = mousePosY;
		camera->firstMouse = false;
	}

	float offsetX = (mousePosX - camera->lastX) * mouseSensivity;
	float offsetY = (camera->lastY - mousePosY) * mouseSensivity;

	camera->lastX = mousePosX;
	camera->lastY = mousePosY;

	camera->rotateByOffset(offsetX, offsetY);
}
