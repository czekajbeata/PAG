#ifndef Core_hpp
#define Core_hpp
#define GLFW_INCLUDE_NONE

#include <memory>

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
	GLfloat deltaTime = 0.0f;		// Czas pomi�dzy obecn� i poprzedni� klatk�
	GLfloat lastTime = 0.0f;		// Czas ostatniej ramki
	float cameraSpeed = 5.0f;
	float mouseSensivity = 0.15f;

	void processInput();
	void processMouse(Scene scene, Model* model);

	std::unique_ptr<Window> window;
	std::unique_ptr<Shader> shader;
	std::unique_ptr<Camera> camera;
	std::unique_ptr<Scene> scene;
	std::unique_ptr<MousePicker> mousePicker;
	std::unique_ptr<UserInterface> ui;
public:
	void run();
	Core();
	~Core();
};

#endif 
