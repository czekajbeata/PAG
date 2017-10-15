#include "Window.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

Window::Window() : Window(WINDOW_WIDTH, WINDOW_HEIGHT, "Window") {}

Window::Window(int width, int height, char* name)
{
	window = glfwCreateWindow(width, height, name, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		throw std::runtime_error("Cannot init window");
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

GLFWwindow * Window::getWindow()
{
	return window;
}
