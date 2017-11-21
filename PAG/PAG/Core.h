#pragma once

#include <stdio.h>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "Const.h"
#include <memory>

class Window;
class Mesh;
class Shader;
class Texture;
class Camera;
class Scene;

class Core
{
private:
	std::unique_ptr<Window> window;
	std::unique_ptr<Mesh> mesh;
	std::unique_ptr<Shader> shader;
	std::unique_ptr<Texture> texture;
	std::unique_ptr<Camera> camera;
	std::unique_ptr<Scene> scene;
	
	float currentTime;

public:
	void run();
	Core();
	~Core();
};
