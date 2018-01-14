#ifndef Core_hpp
#define Core_hpp
#define GLFW_INCLUDE_NONE

#include <memory>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdexcept>
#include <vector>
#include <iostream>
#include "math.h"

#define MAX_BONES = 100;

class Window;
class Mesh;
class Shader;
class Camera;
class Scene;
class MousePicker;
class Model;
class UserInterface;

class Core
{
private:
	GLfloat deltaTime = 0.0f;		// Czas pomiêdzy obecn¹ i poprzedni¹ klatk¹
	GLfloat lastTime = 0.0f;		// Czas ostatniej ramki
	float cameraSpeed = 2.0f;
	float mouseSensivity = 0.15f;

	long long m_startTime;

	void processInput();
	void processMouse(Scene scene, std::vector<Model*> models);

	GLuint m_boneLocation[100];
	GLuint m_prevBoneLocation[100];

	std::unique_ptr<Window> window;
	std::unique_ptr<Shader> defaultShader;
	std::unique_ptr<Shader> skyboxShader;

	std::unique_ptr<Camera> camera;
	std::unique_ptr<Scene> scene;
	std::unique_ptr<MousePicker> mousePicker;
	std::unique_ptr<UserInterface> ui;

	void SetBoneTransform(int Index, const Matrix4f& Transform);
	long long GetCurrentTimeMillis();
public:
	bool isCameraMoving = true;
	void run();
	Core();
	~Core();
};



#endif 
