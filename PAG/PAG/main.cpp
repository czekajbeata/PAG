//#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Core.h"
#include <iostream>

int main()
{

	try {
		Core core;
		core.run();
	}
	catch (std::exception exception) {
		std::cout << exception.what() << std::endl;
		std::cin.get();
	}

	glfwTerminate();
	return 0;
}

