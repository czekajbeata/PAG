#include <stdio.h>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "Core.h"
#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Textures.h"
#include "Transform.h"
#include "Camera.h"
#include "Scene.h"
#include "Material.h"
#include <stdexcept>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Model.h"
#include "MousePicker.h"
#include <iostream>
#include "Node.h"
#include "UserInterface.h"

using namespace std;

void Core::run()
{
	//glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//Transform center = Transform();
	//Transform planet1 = Transform();
	//Transform planet1Moon = Transform();

	//Model model("D:/Studia/Sem V/PAG/PAG/Objects/source/nanosuit.obj", shader.get());
	//Model model("D:/Studia/Sem V/PAG/PAG/Objects/Cubes/source/Cubes.fbx", shader.get());
	//Model model("C:/Users/Beata/Desktop/sem V/PAG/PAG/Objects/Cubes/source/Cubes.fbx", shader.get());
	Model model("C:/Users/Beata/Desktop/sem V/PAG/PAG/Objects/source/nanosuit.obj", shader.get());
	model.getRootNode()->getNodeTransform()->scale(glm::vec3(0.05, 0.05, 0.05));

	while (!glfwWindowShouldClose(window->getWindow()))
	{
		processInput();
		processMouse(*scene, &model);

		glClearColor(BACKGROUND_COLOR);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		glBindVertexArray(mesh->VertexArrayObject);

		GLfloat currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		shader->use();
		//shader->setInt("texture", 0);
		

		////copper
		//glm::vec3 matAmbient = glm::vec3(0.19125f, 0.0735f, 0.0225f);
		//glm::vec3 matDiffuse = glm::vec3(0.7038f, 0.27048f, 0.0828f);
		//glm::vec3 matSpecular = glm::vec3(0.256777f, 0.137622f, 0.086014f);
		//float shininess = 12.8f;

		////unique_ptr<Material> cube = make_unique<Material>(matAmbient, matDiffuse, matSpecular, shininess);

		//shader->setVec3("mambient", matAmbient);
		//shader->setVec3("mdiffuse", matDiffuse);
		//shader->setVec3("mspecular", matSpecular);
		//shader->setFloat("mshininess", shininess);

		//color for directional light - zmienia kolor w czasie 
		glm::vec3 lightColor = glm::vec3(sin(currentTime) * 2.0f , sin(currentTime) *  1.0f , sin(currentTime) *  3.0f);
		//shader->setVec3("lightColor", lightColor);
		glm::vec3 ligDiffuse = lightColor * glm::vec3(0.6f);
		glm::vec3 ligAmbient = ligDiffuse * glm::vec3(0.9f);
		glm::vec3 ligSpecular = glm::vec3(1.0f, 1.0f, 1.0f);
		//shader->setVec3("lambient", ligAmbient);
		//shader->setVec3("ldiffuse", ligDiffuse);
		//shader->setVec3("lspecular", ligSpecular);
		shader->setVec3("lambient", 0.2f, 0.2f, 0.2f);
		shader->setVec3("ldiffuse", 0.5f, 0.5f, 0.5f);
		shader->setVec3("lspecular", 1.0f, 1.0f, 1.0f);
		//shader->setVec3("lightDirection", -0.2f, -1.0f, -0.3f);

		//for spotlight
		shader->setVec3("lightDirection", camera->cameraFront);
		shader->setFloat("lightCutOff", glm::cos(glm::radians(2.5f)));

		shader->setFloat("outerLightCutOff", glm::cos(glm::radians(4.5f)));

		//color for point light  - zmienia intensywnosc w czasie
		glm::vec3 pointLightColor = glm::vec3(1.0f, 1.0f, 1.0f);
		shader->setVec3("pointLightColor", pointLightColor);

		shader->setFloat("pconstant", 1.0f);
		shader->setFloat("plinear", 0.09f);
		shader->setFloat("pquadratic", 0.032f);




		// TO DO: rotates with the smaller cube
		glm::vec3 lightPosition = glm::vec3(0.0f, 2.0f , 3.0f);

		shader->setVec3("lightPosition", lightPosition);
		shader->setVec3("viewPosition", camera->cameraPos);





		scene->updateViewSpace(*camera);
		shader->updateScene(*scene);
//		
//		planet1.setParent(center);
//		planet1.setTransform(center.getTransform());
//		planet1.translate(glm::vec3(0.0f, 0.0f, 1.0f));
//		//planet1.rotate(glm::radians(180.0f) * currentTime, glm::vec3(0.0f, 1.0f, 0.0f));
//		shader->setMat4("model", planet1.getTransform());
////		texture->setActiveTexture(2);
//	//	mesh->draw();
//
//		//light source
//		planet1Moon.setParent(center);
//		planet1Moon.setTransform(planet1.getTransform());
//	//	planet1Moon.rotate(glm::radians(180.0f) * currentTime, glm::vec3(0.0f, 1.0f, 0.0f));
//		planet1Moon.translate(glm::vec3(-1.5f, 1.0f, 1.0f));
//		planet1Moon.scale(glm::vec3(0.5f, 0.5f, 0.5f));
//		shader->setMat4("model", planet1Moon.getTransform());
////		texture->setActiveTexture(2);
////		mesh->draw();

		model.draw(shader.get());
		ui->draw();

		glfwSwapBuffers(window->getWindow());
		glfwPollEvents();
	}
}



Core::Core()
{
	// glfw: initialize and configure
	if (!glfwInit())
		throw runtime_error("Cannot initialize GLFW");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = std::make_unique<Window>();

	// glad: load all OpenGL function pointers
	if (!gladLoadGL())
		throw runtime_error("Cannot initialize GLAD");

	glEnable(GL_DEPTH_TEST);

//	mesh = std::make_unique<Mesh>();
//	mesh->loadContent();

	//texture = std::make_unique<Texture>();

	shader = std::make_unique<Shader>();
	shader->use();

	camera = std::make_unique<Camera>();
	glfwGetCursorPos(window->getWindow(), &camera->lastX, &camera->lastY);

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	scene = std::make_unique<Scene>();
	ui = std::make_unique<UserInterface>(window->getWindow());
	mousePicker = std::make_unique<MousePicker>(*camera, scene->getProjectionSpace());
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

void Core::processMouse(Scene scene, Model* model)
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

	std::pair<int, int> screenSize;
	std::pair<double, double> mousePos;
	glfwGetWindowSize(window->getWindow(), &screenSize.first, &screenSize.second);

	if (glfwGetMouseButton(window->getWindow(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		for each(auto node in model->getAllNodes()) {
			node->setIsSelected(false);
		}
		mousePicker->update(mousePosX, mousePosY);
		auto selectedNode = mousePicker->getSelectedNode(&scene, model, screenSize, mousePos);
		ui->setSelectedNode(selectedNode);
		if (selectedNode != nullptr) {
			selectedNode->setIsSelected(true);
		}
	}
}