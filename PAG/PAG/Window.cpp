#include "Window.h"

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

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

