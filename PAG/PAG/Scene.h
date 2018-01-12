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
	glm::mat4 projectionSpace;
public:
	Scene();
	glm::mat4 getViewSpace();
	glm::mat4 getProjectionSpace();
	void updateViewSpace(Camera& camera);
	~Scene();
};

#endif /* Scene_hpp */
