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
	glUniform1i(glGetUniformLocation(shader->shaderProgram, "texture1"), 0);
	glUniform1i(glGetUniformLocation(shader->shaderProgram, "texture2"), 1);
	
	//render loop
	while (!glfwWindowShouldClose(window->getWindow()))
	{
		// zamknij okno na ESC
		processInput(window->getWindow());

		//update start

		// clear scene			-- render
		glClearColor(BACKGROUND_COLOR);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

		GLint viewLoc = glGetUniformLocation(shader->shaderProgram, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(mesh->View));
		GLint projLoc = glGetUniformLocation(shader->shaderProgram, "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(mesh->Projection));

		//for (unsigned int i = 0; i < 1; i++)
		//{
		//	// calculate the model matrix for each object and pass it to shader before drawing
		//	mesh->Model = glm::translate(mesh->Model, mesh->cubePositions[i]);
		//	float angle = 20.0f * i;
		//	mesh->Model = glm::rotate(mesh->Model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

		//	GLint modelLoc = glGetUniformLocation(shader->shaderProgram, "model");
		//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mesh->Model));


		//	//rysowanie trojkata
		//	mesh->draw();
		//}

		
		//macierz modelu
		glm::mat4 model = glm::mat4(1);
		//glm::translate(model, mesh->cubePositions[1]);
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(20.0f), glm::vec3(1.0f, 0.3f, 0.5f));
		//mesh->Model = glm::rotate(mesh->Model, glm::radians(0.2f), glm::vec3(0.0f, 1.0f, 0.0f));

		GLint modelLoc = glGetUniformLocation(shader->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

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

