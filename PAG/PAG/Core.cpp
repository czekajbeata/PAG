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

		//update start

		// clear scene			-- render
		glClearColor(BACKGROUND_COLOR);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

		////macierz modelu
		//mesh->Model = glm::rotate(mesh->Model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));

		///* Set view matrix */
		//mesh->View = glm::translate(mesh->View, glm::vec3(0.0f, 0.0f, -3.0f));

		///* Set projection matrix */
		//mesh->Projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);




		GLint modelLoc = glGetUniformLocation(shader->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mesh->Model));
		GLint viewLoc = glGetUniformLocation(shader->shaderProgram, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(mesh->View));
		GLint projLoc = glGetUniformLocation(shader->shaderProgram, "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(mesh->Projection));


		//rysowanie trojkata
		mesh->draw();

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)	
		//		-- update
		glfwSwapBuffers(window->getWindow());
		glfwPollEvents();
	}
}

Core::Core() // -- init
{
	// glfw: initialize and configure
	if (!glfwInit())
		throw runtime_error("Cannot initialize GLFW");

	window = unique_ptr<Window>(new Window());

	// glad: load all OpenGL function pointers
	if (!gladLoadGL())
		throw runtime_error("Cannot initialize GLAD");

	/* Enable depth test */
	/* pozwala na ustalenie który wielok¹t przes³ania który */
	glEnable(GL_DEPTH_TEST);

	shader = unique_ptr<Shader>(new Shader());
	// w³¹cznenie programu cieniuj¹cego, który ma byæ u¿yty do renderowania 
	shader->activateShaderProgram(shader->shaderProgram);

	mesh = unique_ptr<Mesh>(new Mesh());

	/* Get uniform location and send MVP matrix there */
//	GLuint wvpLoc = glGetUniformLocation(shader->shaderProgram, "wvp");
//	glUniformMatrix4fv(wvpLoc, 1, GL_FALSE, &(mesh->WVP[0][0]));
	/*	lokalizacja zmiennej w programie cieniuj¹cym - przyjmuje "uchwyt" 
	do programu, który ma shadery i nazwê zmiennej w shaderze
		wysy³anie macierzy z CPU do GPU - lokalizacja, iloœæ wysy³anych macierzy,
	?transponowaæ, adres pierwszego elementu macierzy*/


	//texture = unique_ptr<Texture>(new Texture());



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

