#include "Scene.h"
#include "Shader.h"
#include "Camera.h"
#include "math.h"

Scene::Scene()
{
	projectionSpace = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
}

glm::mat4 Scene::getViewSpace() { return viewSpace; }
glm::mat4 Scene::getProjectionSpace() { return projectionSpace; }
glm::mat4 Scene::getWorldSpace() { return worldSpace; }

void Scene::updateViewSpace(Camera& camera)
{
	viewSpace = glm::lookAt(camera.cameraPos, camera.cameraPos + camera.cameraFront, camera.cameraUp);
}
//
//void Scene::updateWorldSpace(Camera& camera)
//{
//	Matrix4f ScaleTrans, RotateTrans, TranslationTrans;
//
//	ScaleTrans.InitScaleTransform(m_scale.x, m_scale.y, m_scale.z);
//	RotateTrans.InitRotateTransform(m_rotateInfo.x, m_rotateInfo.y, m_rotateInfo.z);
//	TranslationTrans.InitTranslationTransform(m_worldPos.x, m_worldPos.y, m_worldPos.z);
//
//	Matrix4f m_Wtransformation = TranslationTrans * RotateTrans * ScaleTrans;
//	return m_Wtransformation;
//}

Scene::~Scene() {}