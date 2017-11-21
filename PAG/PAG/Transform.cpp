#include "Transform.h"

Transform::Transform()
{
	_transform = glm::mat4(1);
	_parent = nullptr;
}

Transform::Transform(const Transform &)
{
}


Transform::~Transform()
{
}

glm::mat4 Transform::getTransform()
{
	return _transform;
}

void Transform::setTransform(glm::mat4 transform)
{
	this->_transform = transform;
	glm::decompose(this->_transform, _scale, _rotation, _translation, _skew, _perspective);
}

glm::vec3 Transform::getPosition() {
	glm::mat4 transformation = _transform; // your transformation matrix.
	glm::vec3 scale;
	glm::quat rotation;
	glm::vec3 translation;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(transformation, scale, rotation, translation, skew, perspective);
	return translation;
}

void Transform::rotate(float rad, glm::vec3 axis)
{
	_transform = glm::rotate(_transform, rad, axis);
	if (!(_children.empty()))
	{
		for each(auto& child in _children)
		{
			child->rotate(rad, axis);
		}
	}
}

void Transform::translate(glm::vec3 vec)
{
	_transform = glm::translate(_transform, vec);
	if (!(_children.empty()))
	{
		for each(auto& child in _children)
		{
			child->translate(vec);
		}
	}
}

void Transform::scale(glm::vec3 vec)
{
	_transform = glm::scale(_transform, vec);
	if (!(_children.empty()))
	{
		for each(auto& child in _children)
		{
			child->scale(vec);
		}
	}
}

void Transform::setParent(Transform& parent)
{
	_parent = std::make_shared<Transform>(parent);
	parent._children.push_back(std::make_unique<Transform>(*this));
}

