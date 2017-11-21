#include "Camera.h"
#include <iostream>

Camera::Camera()
{	
	firstMouse = true;
	yaw = -90.0f;
	pitch = 0.0f;
	lastX = WINDOW_WIDTH / 2.0f;
	lastY = WINDOW_HEIGHT / 2.0f;
	fov = 45.0f;

	cameraPos = glm::vec3(0.0f, 0.0f, 20.0f);  // camera position in world space
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);  // vector "up
	updateCameraVectors();
}


void Camera::rotateByOffset(float pOffsetX, float pOffsetY)
{
	pitch += pOffsetY;
	yaw += pOffsetX;
	if (pitch > 89.0f)
		pitch = 89.0f;
	else if (pitch < -89.0f)
		pitch = -89.0f;
	updateCameraVectors();
}

void Camera::updateCameraVectors()
{
	glm::vec3 newFront;
	newFront.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	newFront.y = sin(glm::radians(pitch));
	newFront.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	cameraFront = glm::normalize(newFront);
}

Camera::~Camera()
{

}

void Camera::processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	GLfloat speed = cameraSpeed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += speed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= speed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;

	/* Je�li chcemy porusza� si� do przodu lub do ty�u, dodajemy lub odejmujemy
	wektor kierunku od wektora po�o�enia.Je�li chcemy przesuwa� si� na boki,
	wykonujemy iloczyn wektorowy, aby utworzy� prawy wektor i odpowiednio
	porusza� si� wzd�u� tego wektora w prawo. */
}

void Camera::processMouse(GLFWwindow *pWindow)
{
	double mousePosX, mousePosY;
	glfwGetCursorPos(pWindow, &mousePosX, &mousePosY);

	float offsetX = (mousePosX - lastX) * mouseSensivity;
	float offsetY = (lastY - mousePosY) * mouseSensivity; // Odwr�cone, poniewa� wsp�rz�dne y zmieniaj� si� od do�u do g�ry

	lastX = mousePosX;
	lastY = mousePosY;

	rotateByOffset(offsetX, offsetY);
}
