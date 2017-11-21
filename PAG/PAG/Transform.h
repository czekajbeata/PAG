#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtx/matrix_decompose.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <memory>

class Transform
{
private:
	glm::mat4 _transform;
	glm::vec3 _scale;
	glm::quat _rotation;
	glm::vec3 _translation;
	glm::vec3 _skew;
	glm::vec4 _perspective;

	std::vector<std::unique_ptr<Transform>> _children;
	std::shared_ptr<Transform> _parent;

public:
	Transform();
	Transform(const Transform &);
	~Transform();

	glm::mat4 getTransform();
	void setTransform(glm::mat4 transform);

	glm::vec3 getPosition();

	void rotate(float rad, glm::vec3 axis);
	void translate(glm::vec3 vec);
	void scale(glm::vec3 vec);

	void setParent(Transform& parent);

};

