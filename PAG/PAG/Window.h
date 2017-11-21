#include <GLFW/glfw3.h>
#include <stdexcept>

class Window
{
private:
	GLFWwindow *window;
public:
	Window();
	Window(int width, int height, char*);
	GLFWwindow* getWindow();
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
