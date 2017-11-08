#include "Camera.h"

Camera::Camera()
{	
	cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);  // camera position in world space
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f); // point that camera is looking at
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);  // vector "up

	bool firstMouse = true;
	float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	float pitch = 0.0f;
	float lastX = WINDOW_WIDTH / 2.0f;
	float lastY = WINDOW_HEIGHT / 2.0f;
	float fov = 45.0f;
}

Camera::~Camera()
{

}