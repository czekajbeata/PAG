#pragma once

#include <stdio.h>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "Const.h"
#include <memory>

class Window;
class Mesh;
class Shader;
class Texture;
class Camera;


void mouse_callback(GLFWwindow* window, double xpos, double ypos);

class Core
{
private:
	std::unique_ptr<Window> window;
	std::unique_ptr<Mesh> mesh;
	std::unique_ptr<Shader> shader;
	std::unique_ptr<Texture> texture;
	std::unique_ptr<Camera> camera;
	void processInput(GLFWwindow *window);
	void processMouse(GLFWwindow *pWindow);
	//void mouse_callback(GLFWwindow* window, double xpos, double ypos);

	GLfloat deltaTime = 0.0f;  // Czas pomiêdzy obecn¹ i poprzedni¹ klatk¹
	GLfloat lastFrame = 0.0f;    // Czas ostatniej ramki
	float cameraSpeed = 10.0f; // dopasuj do swoich potrzeb
	float mouseSensivity = 0.05f;

public:
	void run();
	Core();
	~Core();
};
