#include "Camera.h"
#include <iostream>

Camera::Camera()
{	
	firstMouse = true;
	yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	pitch = 0.0f;
	lastX = WINDOW_WIDTH / 2.0f;
	lastY = WINDOW_HEIGHT / 2.0f;
	fov = 45.0f;

	cameraPos = glm::vec3(0.0f, 0.0f, 10.0f);  // camera position in world space
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
