#include <stdio.h>
//#include <glm/glm.hpp>
//#include <GLFW/glfw3.h>
//#include <glad/glad.h> 


#include "Mesh.h"
#include "Core.h"
#include "Window.h"
#include "Shader.h"
#include "Texture.h"
#include "Textures.h"
#include "Transform.h"
#include "Camera.h"
#include "Scene.h"
#include "Material.h"
#include "Node.h"
#include "UserInterface.h"
#include "Model.h"
#include "MousePicker.h"
#include "Skybox.h"




using namespace std;

void Core::run()
{
	//glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	std::vector<Model*> models;

	//Model nanosuit("F:/GitHub/PAG_Beatta/PAG/Objects/source/nanosuit.obj", defaultShader.get());
	//Model nanosuit("C:/Users/Beata/Desktop/sem V/PAG/PAG/Objects/source/nanosuit.obj", shader.get());
	Model nanosuit("D:/Studia/Sem V/PAG/PAG/Objects/source/nanosuit.obj", defaultShader.get());
	nanosuit.getRootNode()->getNodeTransform()->scale(glm::vec3(0.05, 0.05, 0.05));
	nanosuit.getRootNode()->getNodeTransform()->translate(glm::vec3(9.0, 0.0, 3.0));

	//Model plane("C:/Users/Beata/Desktop/sem V/PAG/PAG/Objects/source/plane.FBX", shader.get());	
	//Model plane("F:/GitHub/PAG_Beatta/PAG/Objects/source/plane.FBX", defaultShader.get());
	Model plane("D:/Studia/Sem V/PAG/PAG/Objects/source/plane.FBX", defaultShader.get());

	//Model animated("F:/GitHub/PAG_Beatta/PAG/Objects/Robot/source/Robot.fbx", defaultShader.get());
	Model animated("D:/Studia/Sem V/PAG/PAG/Objects/Robot/source/Robot.fbx", defaultShader.get());
	animated.getRootNode()->getNodeTransform()->scale(glm::vec3(0.005, 0.005, 0.005));

	models.push_back(&nanosuit);
	models.push_back(&plane);
	models.push_back(&animated);

	Skybox skybox;
	skybox.setupSkybox();

	defaultShader->setInt("skybox", skybox.cubemapTexture);
	skyboxShader->setInt("skybox", skybox.cubemapTexture);


	//FRAMEBUFFER
	float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
		// positions		 // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		1.0f, -1.0f,  1.0f, 0.0f,
		1.0f,  1.0f,  1.0f, 1.0f
	};

	// screen quad VAO
	unsigned int quadVAO, quadVBO;
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	screenShader->use();
	screenShader->setInt("screenTexture", 0);

	// framebuffer configuration
	// -------------------------
	unsigned int framebuffer;
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	// create a color attachment texture
	unsigned int textureColorbuffer;
	glGenTextures(1, &textureColorbuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);


	screenShader->setInt("depthTexture", 0);
	unsigned int textureDepth;
	glGenTextures(1, &textureDepth);
	glBindTexture(GL_TEXTURE_2D, textureDepth);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_SHORT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	//glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WINDOW_WIDTH, WINDOW_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
	//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
																								  // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, WINDOW_WIDTH, WINDOW_HEIGHT);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, textureDepth, 0);


	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	while (!glfwWindowShouldClose(window->getWindow()))
	{
		processInput();
		processMouse(*scene, models);

		// render
		// ------
		// bind to framebuffer and draw scene as we normally would to color texture 
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)


		glClearColor(BACKGROUND_COLOR);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		GLfloat currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		defaultShader->use();
		//shader->setInt("texture", 0);

		//every light
		glm::vec3 lightColor = glm::vec3(2.0f, 2.0f, 2.0f);
		defaultShader->setVec3("lightColor", lightColor);
		defaultShader->setFloat("currentTime", currentTime);
		defaultShader->setVec3("viewPosition", camera->cameraPos);
		float shininess = 12.8f;
		defaultShader->setFloat("mshininess", shininess);

		//directional light
		glm::vec3 lightDirection = glm::normalize(glm::vec3(-0.2f, -3.0f, -1.3f));
		defaultShader->setVec3("lightDirection", lightDirection);
		//glm::vec3 directionalColors = glm::vec3(0.0f, sin(currentTime) + 1.0f, cos(currentTime) + 1.0f);
		glm::vec3 directionalColors = glm::vec3(0.0f, 1.0f, 1.0f);
		defaultShader->setVec3("directionalColors", directionalColors);

		//point light
		glm::vec3 pointLightPosition = glm::vec3(1, 1, 1.0f);
		//glm::vec3 pointLightPosition = glm::vec3(10 * sin(currentTime), 2.0f, 1.0f);
		defaultShader->setVec3("pointLightPosition", pointLightPosition);

		//spotlight
		defaultShader->setVec3("spotLightPosition", camera->cameraPos);
		defaultShader->setVec3("spotLightDirection", camera->cameraFront);
		defaultShader->setFloat("lightCutOff", glm::cos(glm::radians(3.0f)));
		defaultShader->setFloat("outerLightCutOff", glm::cos(glm::radians(4.5f)));


		//amimation
		vector<Matrix4f> Transforms;
		float RunningTime = (float)((double)GetCurrentTimeMillis() - (double)m_startTime) / 1000.0f;

		//animated.BoneTransform(RunningTime, Transforms);
		//for (int i = 0; i < Transforms.size(); i++) {
		//	SetBoneTransform(i, Transforms[i]);
		//}

		scene->updateViewSpace(*camera);
		defaultShader->updateScene(*scene);


		for each (Model* model in models)
		{
			if (model == &nanosuit)
			{
				defaultShader->setBool("shouldRefract", true);
				defaultShader->setBool("shouldReflect", false);

			}
			else
			{
				defaultShader->setBool("shouldRefract", false);
				defaultShader->setBool("shouldReflect", true);

			}

			model->draw(defaultShader.get());
		}

		skybox.drawContent(skyboxShader.get(), scene.get());

		ui->draw();


		// now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessery actually, since we won't be able to see behind the quad anyways)
		glClear(GL_COLOR_BUFFER_BIT);

		screenShader->use();

		//Depth of field uniforms
		screenShader->setBool("shouldUseDoF", shouldUseDoF);

		glm::vec4 focus = scene->getProjectionSpace() * scene->getViewSpace() * glm::vec4(0, 0, 0, 1);
		float depth = 0.5f * focus.z / focus.w + 0.5f;
		float focusDistance = depth;
	//	float focusDistance = 10.0f;
		float focusTightness = 100.0f;
		screenShader->setFloat("focus_distance", focusDistance);
		screenShader->setFloat("focus_tightness", focusTightness);

		glm::ivec2 screenSize = glm::vec2(WINDOW_WIDTH, WINDOW_HEIGHT);
		screenShader->setVec2("screenSize", screenSize);

		//Pixelization uniforms
		screenShader->setBool("shouldPixelise", shouldPixelise);
		

		glBindVertexArray(quadVAO);
		glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
															  // clear all relevant buffers
		glBindTexture(GL_TEXTURE_2D, textureColorbuffer); // use the color attachment texture as the texture of the quad plane
		glDrawArrays(GL_TRIANGLES, 0, 6);


		glfwSwapBuffers(window->getWindow());
		glfwPollEvents();
	}

	glDeleteFramebuffers(1, &framebuffer);
}



Core::Core()
{
	// glfw: initialize and configure
	if (!glfwInit())
		throw runtime_error("Cannot initialize GLFW");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = std::make_unique<Window>();

	// glad: load all OpenGL function pointers
	if (!gladLoadGL())
		throw runtime_error("Cannot initialize GLAD");

	glEnable(GL_DEPTH_TEST);

	m_startTime = GetCurrentTimeMillis();

	defaultShader = std::make_unique<Shader>();

	defaultShader->loadShader(GL_VERTEX_SHADER, DEFAULT_VERTEX_SHADER_PATH);
	defaultShader->loadShader(GL_FRAGMENT_SHADER, DEFAULT_FRAGMENT_SHADER_PATH);
	defaultShader->link();


	skyboxShader = std::make_unique<Shader>();

	skyboxShader->loadShader(GL_VERTEX_SHADER, SKYBOX_VERTEX_SHADER_PATH);
	skyboxShader->loadShader(GL_FRAGMENT_SHADER, SKYBOX_FRAGMENT_SHADER_PATH);
	skyboxShader->link();

	screenShader = std::make_unique<Shader>();

	screenShader->loadShader(GL_VERTEX_SHADER, SCREEN_VERTEX_SHADER_PATH);
	screenShader->loadShader(GL_FRAGMENT_SHADER, SCREEN_FRAGMENT_SHADER_PATH);
	screenShader->link();



	camera = std::make_unique<Camera>();
	glfwGetCursorPos(window->getWindow(), &camera->lastX, &camera->lastY);

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);


	scene = std::make_unique<Scene>();
	ui = std::make_unique<UserInterface>(window->getWindow());
	mousePicker = std::make_unique<MousePicker>(*camera, scene->getProjectionSpace());

	for (unsigned int i = 0; i < 100; i++) {
		char Name[128];
		memset(Name, 0, sizeof(Name));
		_snprintf_s(Name, sizeof(Name), "gBones[%d]", i);
		m_boneLocation[i] = glGetUniformLocation(defaultShader->getProgram(), Name);
	}
}

Core::~Core()
{
}

void Core::processInput()
{
	if (glfwGetKey(window->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window->getWindow(), true);

	GLfloat speed = deltaTime * cameraSpeed;
	if (glfwGetKey(window->getWindow(), GLFW_KEY_W) == GLFW_PRESS)
		camera->cameraPos += speed * camera->cameraFront;
	if (glfwGetKey(window->getWindow(), GLFW_KEY_S) == GLFW_PRESS)
		camera->cameraPos -= speed * camera->cameraFront;
	if (glfwGetKey(window->getWindow(), GLFW_KEY_A) == GLFW_PRESS)
		camera->cameraPos -= glm::normalize(glm::cross(camera->cameraFront, camera->cameraUp)) * speed;
	if (glfwGetKey(window->getWindow(), GLFW_KEY_D) == GLFW_PRESS)
		camera->cameraPos += glm::normalize(glm::cross(camera->cameraFront, camera->cameraUp)) * speed;
	if (glfwGetKey(window->getWindow(), GLFW_KEY_1) == GLFW_PRESS)
		shouldUseDoF = true;
	if (glfwGetKey(window->getWindow(), GLFW_KEY_2) == GLFW_PRESS)
		shouldUseDoF = false;
	if (glfwGetKey(window->getWindow(), GLFW_KEY_3) == GLFW_PRESS)
		shouldPixelise = true;
	if (glfwGetKey(window->getWindow(), GLFW_KEY_4) == GLFW_PRESS)
		shouldPixelise = false;
}

void Core::processMouse(Scene scene, std::vector<Model*> models)
{
	double mousePosX, mousePosY;
	glfwGetCursorPos(window->getWindow(), &mousePosX, &mousePosY);

	if (camera->firstMouse)
	{
		camera->lastX = mousePosX;
		camera->lastY = mousePosY;
		camera->firstMouse = false;
	}

	float offsetX = (mousePosX - camera->lastX) * mouseSensivity;
	float offsetY = (camera->lastY - mousePosY) * mouseSensivity;

	camera->lastX = mousePosX;
	camera->lastY = mousePosY;

	if (isCameraMoving) {

		camera->rotateByOffset(offsetX, offsetY);
	}


	std::pair<int, int> screenSize;
	std::pair<double, double> mousePos;
	mousePos.first = mousePosX;
	mousePos.second = mousePosY;
	glfwGetWindowSize(window->getWindow(), &screenSize.first, &screenSize.second);

	if (glfwGetMouseButton(window->getWindow(), GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
		if (isCameraMoving) {
			isCameraMoving = false;
		}
		else {
			isCameraMoving = true;
		}
	}

	if (glfwGetMouseButton(window->getWindow(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {

		for each (Model* model in models)
		{
			for each(auto node in model->getAllNodes()) {
				node->setIsSelected(false);
			}
		}
		mousePicker->update(mousePosX, mousePosY);
		auto selectedNode = mousePicker->getSelectedNode(&scene, models, screenSize, mousePos);
		ui->setSelectedNode(selectedNode);
		if (selectedNode != nullptr) {
			selectedNode->setIsSelected(true);
		}
	}
}

long long Core::GetCurrentTimeMillis()
{
#ifdef WIN32    
	return GetTickCount();
#else
	timeval t;
	gettimeofday(&t, NULL);

	long long ret = t.tv_sec * 1000 + t.tv_usec / 1000;
	return ret;
#endif    
}

void Core::SetBoneTransform(int Index, const Matrix4f& Transform)
{
	assert(Index < 100);
	//Transform.Print();
	glUniformMatrix4fv(m_boneLocation[Index], 1, GL_TRUE, (const GLfloat*)Transform);
}

