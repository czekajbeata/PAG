#include "Transform.h"
#include <assimp/scene.h>

#pragma region Constructors/Destructors
Transform::Transform()
{
	setTransform(glm::mat4(1));
	_parent = std::shared_ptr<Transform>();
	sharedPtrOfThis = std::make_shared<Transform>(*this);
}

Transform::Transform(const Transform & value)
{
	setTransform(value._transform);
	_parent = value._parent;
}
#pragma endregion

#pragma region Getters/Setters
glm::mat4 Transform::getTransform()
{
	return _transform;
}

void Transform::setTransform(glm::mat4 transform)
{
	this->_transform = transform;
	glm::decompose(transform, _scale, _rotation, _position, _skew, _perspective);
}

void Transform::update() {
	glm::mat4 transform = glm::mat4(1);
	transform = glm::translate(transform, _position);
	transform = glm::rotate(transform, _rotationAngle, _rotationAxis);
	transform = glm::scale(transform, _scale);
	setTransform(transform);
}

glm::vec3 Transform::getPosition() {
	return _position;
}

glm::vec3 Transform::getScale()
{
	return _scale;
}

glm::quat Transform::getRotation()
{
	return _rotation;
}

void Transform::setPosition(glm::vec3 position)
{
	_position = position;
	update();
}

const std::pair<glm::vec3, float> Transform::getRotationAxisAndAngle()
{
	return std::pair<glm::vec3, float>(_rotationAxis, _rotationAngle);
}

void Transform::setScale(glm::vec3 scale)
{
	_scale = scale;
	update();
}
void Transform::setRotation(float rad, glm::vec3 axis)
{
	_rotationAngle = rad;
	_rotationAxis = axis;
	update();
}
#pragma endregion

void Transform::rotate(float rad, glm::vec3 axis)
{
	_rotationAngle = rad;
	_rotationAxis = axis;
	setTransform(glm::rotate(_transform, rad, axis));
}

void Transform::translate(glm::vec3 translation)
{
	setTransform(glm::translate(_transform, translation));
}

void Transform::scale(glm::vec3 scale)
{
	setTransform(glm::scale(_transform, scale));
}

void Transform::importAiTransform(aiMatrix4x4 pMatrix)
{
	aiVector3t<float> aiScale, aiPosition;
	aiQuaterniont<float> aiRotation;

	glm::quat gRotation;

	pMatrix.Decompose(aiScale, aiRotation, aiPosition);

	gRotation.w = aiRotation.w;
	gRotation.x = aiRotation.x;
	gRotation.y = aiRotation.y;
	gRotation.z = aiRotation.z;

	translate(glm::vec3(aiPosition.x, aiPosition.y, aiPosition.z));
	scale(glm::vec3(aiScale.x, aiScale.y, aiScale.z));
	rotate(glm::angle(gRotation), glm::axis(gRotation));
}