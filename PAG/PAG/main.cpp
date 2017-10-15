#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Core.h"
#include <iostream>


int main()
{

	try {
		Core core;
		core.run();
	}
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
		std::system("PAUSE");
		return -1;
	}

	glfwTerminate();
	return 0;
}

