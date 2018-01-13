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




using namespace std;

void Core::run()
{
	//glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//Transform center = Transform();
	//Transform planet1 = Transform();
	//Transform planet1Moon = Transform();

	std::vector<Model*> models;

	//Model nanosuit("D:/Studia/Sem V/PAG/PAG/Objects/source/nanosuit.obj", shader.get());
	//Model cubes("D:/Studia/Sem V/PAG/PAG/Objects/Cubes/source/Cubes.fbx", shader.get());
	////Model cubes("C:/Users/Beata/Desktop/sem V/PAG/PAG/Objects/Cubes/source/Cubes.fbx", shader.get());
	//cubes.getRootNode()->getNodeTransform()->scale(glm::vec3(0.002, 0.002, 0.002));
	////Model nanosuit("C:/Users/Beata/Desktop/sem V/PAG/PAG/Objects/source/nanosuit.obj", shader.get());
	//nanosuit.getRootNode()->getNodeTransform()->scale(glm::vec3(0.05, 0.05, 0.05));
	////Model plane("C:/Users/Beata/Desktop/sem V/PAG/PAG/Objects/source/plane.FBX", shader.get());
	//Model plane("D:/Studia/Sem V/PAG/PAG/Objects/source/plane.FBX", shader.get());
	Model animated("D:/Studia/Sem V/PAG/PAG/Objects/Robot/source/Robot.fbx", shader.get());

	animated.getRootNode()->getNodeTransform()->scale(glm::vec3(0.05, 0.05, 0.05));
//	models.push_back(&cubes);
//	models.push_back(&nanosuit);
//	models.push_back(&plane);
	models.push_back(&animated);

	while (!glfwWindowShouldClose(window->getWindow()))
	{
		processInput();
		processMouse(*scene, models);

		glClearColor(BACKGROUND_COLOR);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		GLfloat currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;



		shader->use();
		//shader->setInt("texture", 0);
		

		////copper
		//glm::vec3 matAmbient = glm::vec3(0.19125f, 0.0735f, 0.0225f);
		//glm::vec3 matDiffuse = glm::vec3(0.7038f, 0.27048f, 0.0828f);
		//glm::vec3 matSpecular = glm::vec3(0.256777f, 0.137622f, 0.086014f);/*
		glm::vec3 matAmbient = glm::vec3(0.2f, 0.2f, 0.2f);
		glm::vec3 matDiffuse = glm::vec3(0.2f, 0.2f, 0.2f);
		glm::vec3 matSpecular = glm::vec3(0.2f, 0.2f, 0.2f);
		float shininess = 12.8f;

		////unique_ptr<Material> cube = make_unique<Material>(matAmbient, matDiffuse, matSpecular, shininess);

		shader->setVec3("mambient", matAmbient);
		shader->setVec3("mdiffuse", matDiffuse);
		shader->setVec3("mspecular", matSpecular);
		shader->setFloat("mshininess", shininess);

	
		//glm::vec3 ligDiffuse = lightColor * glm::vec3(0.6f);
		//glm::vec3 ligAmbient = ligDiffuse * glm::vec3(0.9f);
		//glm::vec3 ligSpecular = glm::vec3(1.0f, 1.0f, 1.0f);
		////shader->setVec3("lambient", ligAmbient);
		////shader->setVec3("ldiffuse", ligDiffuse);
		////shader->setVec3("lspecular", ligSpecular);
		//shader->setVec3("lambient", 0.2f, 0.2f, 0.2f);
		//shader->setVec3("ldiffuse", 0.5f, 0.5f, 0.5f);
		//shader->setVec3("lspecular", 1.0f, 1.0f, 1.0f);

		//every light
		glm::vec3 lightColor = glm::vec3(2.0f, 2.0f, 2.0f);
		shader->setVec3("lightColor", lightColor);
		shader->setFloat("currentTime", currentTime);
		shader->setVec3("viewPosition", camera->cameraPos);


		//directional light
		glm::vec3 lightDirection = glm::normalize(glm::vec3(-0.2f, -3.0f, -1.3f));
		shader->setVec3("lightDirection", lightDirection);
		glm::vec3 directionalColors = glm::vec3( 0.0f, sin(currentTime) + 1.0f, cos(currentTime)+1.0f);
		shader->setVec3("directionalColors", directionalColors);

		//point light
		//glm::vec3 pointLightPosition = glm::vec3(1, 1, 1.0f);
		glm::vec3 pointLightPosition = glm::vec3(10*sin(currentTime), 2.0f, 1.0f);
		shader->setVec3("pointLightPosition", pointLightPosition);

		//spotlight
		shader->setVec3("spotLightPosition", camera->cameraPos);
		shader->setVec3("spotLightDirection", camera->cameraFront);
		shader->setFloat("lightCutOff", glm::cos(glm::radians(3.0f)));
		shader->setFloat("outerLightCutOff", glm::cos(glm::radians(4.5f)));


		//running time
		//bone transform
		//set bone transform


		vector<Matrix4f> Transforms;
		float RunningTime = (float)((double)GetCurrentTimeMillis() - (double)m_startTime) / 1000.0f;

		animated.BoneTransform(RunningTime, Transforms);
		for (int i = 0; i < Transforms.size(); i++) {
			SetBoneTransform(i, Transforms[i]);
		}


		//przekaz world transform do shadera
		//Normal = (gWorld * Normal).xyz;
		//WorldPos0 = (gWorld * FragPos).xyz;

		scene->updateViewSpace(*camera);
		shader->updateScene(*scene);

		for each (Model* model in models)
		{
			model->draw(shader.get());
		}

		ui->draw();

		glfwSwapBuffers(window->getWindow());
		glfwPollEvents();
	}
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

	shader = std::make_unique<Shader>();
	shader->use();

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
		m_boneLocation[i] = glGetUniformLocation(shader->getProgram(), Name);
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