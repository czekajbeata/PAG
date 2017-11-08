#include "Core.h"
#include "Window.h"
#include "Mesh.h"
#include "Camera.h"
#include "Shader.h"
#include "Texture.h"
#include "Transform.h"
#include <exception>
#include <stdexcept>

using namespace std;

void Core::run()
{	
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


		///* Set model matrix */
		Transform center = Transform();
		center.rotate((float)glfwGetTime() * glm::radians(60.0f), glm::vec3(0.0f, 1.0f, 0.5f));
		center.scale(glm::vec3(2, 2, 2));
		glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "model"), 1, GL_FALSE, &center.transform[0][0]);
		texture->setActiveTexture(0);
		mesh->draw();

		Transform planet1 = Transform();
		planet1.transform = center.transform;
		planet1.rotate((float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // wokó³ centrum
		planet1.translate(glm::vec3(4.5f, 0.0f, 0.0f)); // zmienia siê po³o¿enie
		planet1.rotate((float)glfwGetTime() * glm::radians(60.0f), glm::vec3(0.0f, 1.0f, 1.0f)); // wokó³ swojej osi
		glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "model"), 1, GL_FALSE, &planet1.transform[0][0]);
		texture->setActiveTexture(1);
		mesh->draw();

		Transform planet1Moon = Transform();
		planet1Moon.transform = planet1.transform; // pocz¹tkowe po³o¿enie jak rodzica
		planet1Moon.rotate((float)glfwGetTime() * glm::radians(-500.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // wokó³ rodzica
		planet1Moon.translate(glm::vec3(1.5f, 0.0f, 0.0f)); // przesuniêcie od rodzica
		planet1Moon.rotate((float)glfwGetTime() * glm::radians(-60.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // wokó³ w³asnej osi
		planet1Moon.scale(glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "model"), 1, GL_FALSE, &planet1Moon.transform[0][0]);
		texture->setActiveTexture(2);
		mesh->draw();

		Transform planet2 = Transform();
		planet2.transform = center.transform;
		planet2.rotate((float)glfwGetTime() * glm::radians(150.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		planet2.translate(glm::vec3(13.0f, 0.0f, 0.0f));
		planet2.rotate((float)glfwGetTime() * glm::radians(360.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		planet2.scale(glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "model"), 1, GL_FALSE, &planet2.transform[0][0]);
		texture->setActiveTexture(0);
		mesh->draw();

		Transform planet3 = Transform();
		planet3.transform = center.transform;
		planet3.rotate((float)glfwGetTime() * glm::radians(170.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		planet3.translate(glm::vec3(5.0f, 0.0f, 0.0f));
		planet3.rotate((float)glfwGetTime() * glm::radians(60.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		planet3.scale(glm::vec3(0.55f, 0.55f, 0.55f));
		glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "model"), 1, GL_FALSE, &planet3.transform[0][0]);
		texture->setActiveTexture(1);
		mesh->draw();

		Transform planet3Moon1 = Transform();
		planet3Moon1.transform = planet3.transform; // pocz¹tkowe po³o¿enie jak rodzica
		planet3Moon1.rotate((float)glfwGetTime() * glm::radians(-50.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // wokó³ rodzica
		planet3Moon1.translate(glm::vec3(1.2f, 0.0f, 0.0f)); // przesuniêcie od rodzica
		planet3Moon1.rotate((float)glfwGetTime() * glm::radians(-60.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // wokó³ w³asnej osi
		planet3Moon1.scale(glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "model"), 1, GL_FALSE, &planet3Moon1.transform[0][0]);
		texture->setActiveTexture(2);
		mesh->draw();

		Transform planet3Moon2 = Transform();
		planet3Moon2.transform = planet3.transform; // pocz¹tkowe po³o¿enie jak rodzica
		planet3Moon2.rotate((float)glfwGetTime() * glm::radians(-400.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // wokó³ rodzica
		planet3Moon2.translate(glm::vec3(1.4f, 0.0f, 0.0f)); // przesuniêcie od rodzica
		planet3Moon2.rotate((float)glfwGetTime() * glm::radians(-300.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // wokó³ w³asnej osi
		planet3Moon2.scale(glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "model"), 1, GL_FALSE, &planet3Moon2.transform[0][0]);
		texture->setActiveTexture(1);
		mesh->draw();

		Transform planet4 = Transform();
		planet4.transform = center.transform;
		planet4.rotate((float)glfwGetTime() * glm::radians(120.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		planet4.translate(glm::vec3(0.0f, 3.0f, 0.0f));
		planet4.rotate((float)glfwGetTime() * glm::radians(130.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		planet4.scale(glm::vec3(0.15f, 0.15f, 0.15f));
		glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "model"), 1, GL_FALSE, &planet4.transform[0][0]);
		texture->setActiveTexture(0);
		mesh->draw();

		Transform planet5 = Transform();
		planet5.transform = center.transform;
		planet5.rotate((float)glfwGetTime() * glm::radians(70.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		planet5.translate(glm::vec3(10.0f, 0.0f, 0.0f));
		planet5.rotate((float)glfwGetTime() * glm::radians(260.0f), glm::vec3(0.0f, 1.0f, 1.0f));
		planet5.scale(glm::vec3(0.75f, 0.75f, 0.75f));
		glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "model"), 1, GL_FALSE, &planet5.transform[0][0]);
		texture->setActiveTexture(2);
		mesh->draw();

		Transform planet5Moon1 = Transform();
		planet5Moon1.transform = planet3.transform; // pocz¹tkowe po³o¿enie jak rodzica
		planet5Moon1.rotate((float)glfwGetTime() * glm::radians(-150.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // wokó³ rodzica
		planet5Moon1.translate(glm::vec3(0.0f, 2.0f, 0.0f)); // przesuniêcie od rodzica
		planet5Moon1.rotate((float)glfwGetTime() * glm::radians(-60.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // wokó³ w³asnej osi
		planet5Moon1.scale(glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "model"), 1, GL_FALSE, &planet5Moon1.transform[0][0]);
		texture->setActiveTexture(1);
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

	mesh = unique_ptr<Mesh>(new Mesh());
	camera = unique_ptr<Camera>(new Camera());
	texture = unique_ptr<Texture>(new Texture());

	shader = unique_ptr<Shader>(new Shader());
	// w³¹cznenie programu cieniuj¹cego, który ma byæ u¿yty do renderowania 
	shader->activateShaderProgram(shader->shaderProgram);
	glUniform1i(glGetUniformLocation(shader->shaderProgram, "texture"), 0);

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

	float offsetX = (mousePosX - camera->lastX) * mouseSensivity;
	float offsetY = (camera->lastY - mousePosY) * mouseSensivity; // Odwrócone, poniewa¿ wspó³rzêdne y zmieniaj¹ siê od do³u do góry

	camera->lastX = mousePosX;
	camera->lastY = mousePosY;

	camera->rotateByOffset(offsetX, offsetY);
}
