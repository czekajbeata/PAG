#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Camera
{
private:
	void Camera::updateCameraVectors();
	void Camera::rotateByOffset(float pOffsetX, float pOffsetY);
	
	float cameraSpeed = 10.0f; 
	float mouseSensivity = 0.05f;

public:
	Camera();
	~Camera();

	//camera set-up
	bool firstMouse;
	float yaw;
	float pitch;
	double lastX;
	double lastY;
	float fov;

	glm::vec3 cameraPos; 
	glm::vec3 cameraFront;
	glm::vec3 cameraUp; 
	GLfloat deltaTime = 0.0f;  // Czas pomiêdzy obecn¹ i poprzedni¹ klatk¹
	GLfloat lastFrame = 0.0f;    // Czas ostatniej ramki
	
	void processInput(GLFWwindow *window);
	void processMouse(GLFWwindow *pWindow);
};

