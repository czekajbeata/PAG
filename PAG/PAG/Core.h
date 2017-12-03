#ifndef Core_hpp
#define Core_hpp
#define GLFW_INCLUDE_NONE

#include <memory>

class Window;
class Mesh;
class Shader;
class Texture;
class Camera;
class Scene;

class Core
{
private:
	GLfloat deltaTime = 0.0f;		// Czas pomi�dzy obecn� i poprzedni� klatk�
	GLfloat lastTime = 0.0f;		// Czas ostatniej ramki
	float cameraSpeed = 20.0f;
	float mouseSensivity = 0.05f;

	void processInput();
	void processMouse();

	std::unique_ptr<Window> window;
	std::unique_ptr<Mesh> mesh;
	std::unique_ptr<Shader> shader;
	std::unique_ptr<Texture> texture;
	std::unique_ptr<Camera> camera;
	std::unique_ptr<Scene> scene;
public:
	void run();
	Core();
	~Core();
};

#endif 
