#include "Core.h"
#include "Window.h"
#include "Mesh.h"
#include "Camera.h"
#include "Shader.h"
#include "Texture.h"
#include <exception>
#include <stdexcept>

using namespace std;

void Core::run()
{
	glUniform1i(glGetUniformLocation(shader->shaderProgram, "texture1"), 0);
	glUniform1i(glGetUniformLocation(shader->shaderProgram, "texture2"), 1);
	
	// ukrywanie i przechwytywanie kursora myszy
	glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//render loop
	while (!glfwWindowShouldClose(window->getWindow()))
	{
		//get time values
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// zamknij okno na ESC
		processInput(window->getWindow());
		processMouse(window->getWindow());
		
		// -- DISPLAY --

		// clear scene			-- render
		glClearColor(BACKGROUND_COLOR);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/* Set project matrix */
		GLint projLoc = glGetUniformLocation(shader->shaderProgram, "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(mesh->Projection));

		/* Set view matrix */
		glm::mat4 View = glm::lookAt(camera->cameraPos, camera->cameraPos + camera->cameraFront, camera->cameraUp);
		// Euler = pitch: góra/dó³	yaw: lewo/prawo	roll: turlanie
		GLint viewLoc = glGetUniformLocation(shader->shaderProgram, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(View));


		/* Set model matrix */
		//macierz modelu 1 
		glm::mat4 firstModel = glm::mat4(1);
		firstModel = glm::rotate(firstModel, (float)glfwGetTime() * glm::radians(20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//	firstModel = glm::rotate(firstModel, glm::radians(20.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // not moving
		GLint firstLoc = glGetUniformLocation(shader->shaderProgram, "model");
		glUniformMatrix4fv(firstLoc, 1, GL_FALSE, glm::value_ptr(firstModel));
		mesh->draw();

		//macierz modelu 1 
		glm::mat4 secondModel = glm::mat4(1);
		secondModel = glm::rotate(secondModel, (float)glfwGetTime() * glm::radians(20.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // wokó³ s³oñca
		secondModel = glm::translate(secondModel, glm::vec3(3.0f, 0.0f, 0.0f));
		secondModel = glm::rotate(secondModel, (float)glfwGetTime() * glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f)); //wokó³ w³asnej osi
		GLint secondLoc = glGetUniformLocation(shader->shaderProgram, "model");
		glUniformMatrix4fv(secondLoc, 1, GL_FALSE, glm::value_ptr(secondModel));
		mesh->draw();

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
	camera = unique_ptr<Camera>(new Camera());
	texture = unique_ptr<Texture>(new Texture());

	glfwGetCursorPos(window->getWindow(), &camera->lastX, &camera->lastY);

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}

Core::~Core()
{
}

void Core::processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	GLfloat cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->cameraPos += cameraSpeed * camera->cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->cameraPos -= cameraSpeed * camera->cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->cameraPos -= glm::normalize(glm::cross(camera->cameraFront, camera->cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->cameraPos += glm::normalize(glm::cross(camera->cameraFront, camera->cameraUp)) * cameraSpeed;

	/* Jeœli chcemy poruszaæ siê do przodu lub do ty³u, dodajemy lub odejmujemy 
	wektor kierunku od wektora po³o¿enia.Jeœli chcemy przesuwaæ siê na boki,
	wykonujemy iloczyn wektorowy, aby utworzyæ prawy wektor i odpowiednio 
	poruszaæ siê wzd³u¿ tego wektora w prawo. */
}

void Core::processMouse(GLFWwindow *pWindow)
{

	double mousePosX, mousePosY;
	glfwGetCursorPos(pWindow, &mousePosX, &mousePosY);

	if (camera->firstMouse)
	{
		camera->lastX = mousePosX;
		camera->lastY = mousePosY;
		camera->firstMouse = false;
	}

	float offsetX = (mousePosX - camera->lastX) * mouseSensivity;
	float offsetY = (camera->lastY - mousePosY) * mouseSensivity; // Odwrócone, poniewa¿ wspó³rzêdne y zmieniaj¹ siê od do³u do góry

	camera->lastX = mousePosX;
	camera->lastY = mousePosY;

	camera->rotateByOffset(offsetX, offsetY);
}
