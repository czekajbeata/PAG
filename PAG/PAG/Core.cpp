#include "Core.h"
#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include <exception>
#include <stdexcept>

using namespace std;

void Core::run()
{
	glUniform1i(glGetUniformLocation(shader->shaderProgram, "ourTexture1"), 1);
	glUniform1i(glGetUniformLocation(shader->shaderProgram, "ourTexture2"), 0);
	
	//render loop
	while (!glfwWindowShouldClose(window->getWindow()))
	{
		// zamknij okno na ESC
		processInput(window->getWindow());

		// clear scene
		glClearColor(BACKGROUND_COLOR);
		glClear(GL_COLOR_BUFFER_BIT);
	
		//rysowanie trojkata
		mesh->draw();

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window->getWindow());
		glfwPollEvents();
	}
}

Core::Core()
{
	// glfw: initialize and configure
	if (!glfwInit())
		throw runtime_error("Cannot initialize GLFW");

	window = unique_ptr<Window>(new Window());

	// glad: load all OpenGL function pointers
	if (!gladLoadGL())
		throw runtime_error("Cannot initialize GLAD");

	mesh = unique_ptr<Mesh>(new Mesh());

	shader = unique_ptr<Shader>(new Shader());
	// w³¹cznenie programu cieniuj¹cego, który ma byæ u¿yty do renderowania 
	shader->activateShaderProgram(shader->shaderProgram);

	texture = unique_ptr<Texture>(new Texture());

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}

Core::~Core()
{
}

void Core::processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

