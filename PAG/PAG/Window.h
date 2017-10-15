#ifndef Window_h
#define Window_h
#include <GLFW/glfw3.h>
#include <stdexcept>
#include "Const.h"

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// -------
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

class Window
{
private:
	GLFWwindow *window;
public:
	Window();
	Window(int width, int height, char*);
	GLFWwindow* getWindow();
};


#endif Window_h