#ifndef Scene_hpp
#define Scene_hpp

#include <stdio.h>
#include <glm/glm.hpp>
#include "Const.h"
#include <memory>

class Shader;
class Camera;

class Scene
{
private:
	glm::mat4 viewSpace;
	glm::mat4 worldSpace;
	glm::mat4 projectionSpace;
public:
	Scene();
	glm::mat4 getViewSpace();
	glm::mat4 getProjectionSpace();
	glm::mat4 getWorldSpace();
	void updateViewSpace(Camera& camera);
	//void updateWorldSpace(Camera& camera);
	~Scene();
};

#endif /* Scene_hpp */
