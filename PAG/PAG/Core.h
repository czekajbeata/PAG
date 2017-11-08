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
	void processInput(GLFWwindow *window);
	std::unique_ptr<Camera> camera;
	//void mouse_callback(GLFWwindow* window, double xpos, double ypos);

	GLfloat deltaTime = 0.0f;  // Czas pomiêdzy obecn¹ i poprzedni¹ klatk¹
	GLfloat lastFrame = 0.0f;    // Czas ostatniej ramki
	float cameraSpeed = 0.07f; // dopasuj do swoich potrzeb

public:
	void run();
	Core();
	~Core();
};
