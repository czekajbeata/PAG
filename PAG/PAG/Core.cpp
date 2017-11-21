#include "Core.h"
#include "Window.h"
#include "Mesh.h"
#include "Camera.h"
#include "Shader.h"
#include "Scene.h"
#include "TextureLoader.h"
#include "Transform.h"
#include "Model.h"
#include "Const.h"
#include <exception>
#include <stdexcept>

using namespace std;

void Core::run()
{	
	Model model("C:/Users/BeataPC/Downloads/PAG-models/PAG/Objects/nanosuit.obj");
	// ukrywanie i przechwytywanie kursora myszy
//	glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//render loop
	while (!glfwWindowShouldClose(window->getWindow()))
	{
		//get time values
		GLfloat currentFrame = glfwGetTime();
		camera->deltaTime = currentFrame - camera->lastFrame;
		camera->lastFrame = currentFrame;

		currentTime = (float)glfwGetTime();
		//currentTime = 0;
		float scale = sin(currentTime);

		camera->processInput(window->getWindow());
		camera->processMouse(window->getWindow());

		// clear scene		
		glClearColor(BACKGROUND_COLOR);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		///* Set view matrix */
		glm::mat4 View = glm::lookAt(camera->cameraPos, camera->cameraPos + camera->cameraFront, camera->cameraUp);
		scene->updateViewSpace(View);
		scene->updateSpace(shader->shaderProgram);


		glm::mat4 newModel = glm::mat4(1);
		newModel = glm::translate(newModel, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
		newModel = glm::scale(newModel, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
		glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "model"), 1, GL_FALSE, &newModel[0][0]);

		model.Draw(shader->shaderProgram);
		
		// after center - always facing front
		//glm::vec3 F = glm::normalize(camera->cameraPos - center.getPosition());
		//glm::vec3 R = glm::normalize(glm::cross(F, glm::vec3(0.0, 1.0, 0.0)));
		//glm::vec3 U = glm::normalize(glm::cross(F, R));
		//glm::mat4 cube = glm::mat4(glm::vec4(F, 0.0), glm::vec4(R, 0.0), glm::vec4(U, 0.0), glm::vec4(center.getPosition(), 1.0));


		/////* Set model matrix */
		//Transform center = Transform();
		//center.rotate(currentTime * glm::radians(60.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//center.scale(glm::vec3(2, 2, 2));
		//glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "model"), 1, GL_FALSE, &center.getTransform()[0][0]);
		//texture->setActiveTexture(1);
		//mesh->draw();

		//Transform planet1 = Transform();
		//planet1.setParent(center);
		//planet1.setTransform(center.getTransform());
		////planet1.rotate(currentTime * glm::radians(5.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // wokó³ centrum
		//planet1.translate(glm::vec3(4.5f, 0.0f, 0.0f)); // zmienia siê po³o¿enie
		////planet1.rotate(currentTime * glm::radians(6.0f), glm::vec3(0.0f, 1.0f, 1.0f)); // wokó³ swojej osi
		//glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "model"), 1, GL_FALSE, &planet1.getTransform()[0][0]);
		//texture->setActiveTexture(1);
		//mesh->draw();

		//Transform planet1Moon = Transform();
		//planet1Moon.setParent(planet1);
		//planet1Moon.setTransform(planet1.getTransform()); // pocz¹tkowe po³o¿enie jak rodzica
		////planet1Moon.rotate(currentTime * glm::radians(-5.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // wokó³ rodzica
		//planet1Moon.translate(glm::vec3(1.5f, 0.0f, 0.0f)); // przesuniêcie od rodzica
		////planet1Moon.rotate(currentTime * glm::radians(-6.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // wokó³ w³asnej osi
		////planet1Moon.scale(glm::vec3(scale, scale, scale));
		//glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "model"), 1, GL_FALSE, &planet1Moon.getTransform()[0][0]);
		//texture->setActiveTexture(2);
		//mesh->draw();

		//Transform planet2 = Transform();
		//planet2.setParent(center);
		//planet2.setTransform(center.getTransform());
		////planet2.rotate(currentTime * glm::radians(15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//planet2.translate(glm::vec3(8.0f, 0.0f, 0.0f));
		////planet2.rotate(currentTime * glm::radians(36.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//planet2.scale(glm::vec3(0.5f, 0.5f, 0.5f));
		//glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "model"), 1, GL_FALSE, &planet2.getTransform()[0][0]);
		//texture->setActiveTexture(0);
		//mesh->draw();

		//Transform planet3 = Transform();
		//planet3.setParent(center);
		//planet3.setTransform(center.getTransform());
		//planet3.rotate(currentTime * glm::radians(100.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//planet3.translate(glm::vec3(3.0f, 0.0f, 0.0f));
		////planet3.rotate(currentTime * glm::radians(6.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//planet3.scale(glm::vec3(0.55f, 0.55f, 0.55f));
		//glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "model"), 1, GL_FALSE, &planet3.getTransform()[0][0]);
		//texture->setActiveTexture(1);
		//mesh->draw();

		//Transform planet3Moon1 = Transform();
		//planet3Moon1.setParent(planet3);
		//planet3Moon1.setTransform(planet3.getTransform()); // pocz¹tkowe po³o¿enie jak rodzica
		////planet3Moon1.rotate(currentTime * glm::radians(-150.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // wokó³ rodzica
		//planet3Moon1.translate(glm::vec3(1.2f, 0.0f, 0.0f)); // przesuniêcie od rodzica
		////planet3Moon1.rotate(currentTime * glm::radians(-6.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // wokó³ w³asnej osi
		//planet3Moon1.scale(glm::vec3(0.25f, 0.25f, 0.25f));
		//glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "model"), 1, GL_FALSE, &planet3Moon1.getTransform()[0][0]);
		//texture->setActiveTexture(2);
		//mesh->draw();

		//Transform planet3Moon2 = Transform();
		//planet3Moon1.setParent(planet3);
		//planet3Moon2.setTransform(planet3.getTransform()); // pocz¹tkowe po³o¿enie jak rodzica
		////planet3Moon2.rotate(currentTime * glm::radians(-4.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // wokó³ rodzica
		//planet3Moon2.translate(glm::vec3(1.4f, 0.0f, 0.0f)); // przesuniêcie od rodzica
		////planet3Moon2.rotate(currentTime * glm::radians(-3.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // wokó³ w³asnej osi
		//planet3Moon2.scale(glm::vec3(0.2f, 0.2f, 0.2f));
		//glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "model"), 1, GL_FALSE, &planet3Moon2.getTransform()[0][0]);
		//texture->setActiveTexture(1);
		//mesh->draw();


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

	//mesh = unique_ptr<Mesh>(new Mesh());
	camera = unique_ptr<Camera>(new Camera());	
	texture = std::make_unique<TextureLoader>();

	shader = unique_ptr<Shader>(new Shader());
	// w³¹cznenie programu cieniuj¹cego, który ma byæ u¿yty do renderowania 
	shader->activateShaderProgram(shader->shaderProgram);
	glUniform1i(glGetUniformLocation(shader->shaderProgram, "texture"), 0);
	
	scene = unique_ptr<Scene>(new Scene());

	//model = unique_ptr<Model>(new Model("source/Dio.obj"));


	glfwGetCursorPos(window->getWindow(), &camera->lastX, &camera->lastY);

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}

Core::~Core()
{
}

