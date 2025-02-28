#ifndef Shader_hpp
#define Shader_hpp

#include <glad/glad.h>
#include <string>
#include "FileReader.h"
#include "Const.h"
#include <glm/glm.hpp>

class Scene;

class Shader
{
private:
	GLuint program;
public:
	void loadShader(GLint type, std::string fileName);
	void link();
	GLuint getProgram();
	void updateScene(Scene scene);
	void use();
	void setBool(const std::string & name, bool value) const;
	void setInt(const std::string & name, int value) const;
	void setFloat(const std::string & name, float value) const;
	void setVec2(const std::string & name, const glm::vec2 & value) const;
	void setVec2(const std::string & name, float x, float y) const;
	Shader();
	~Shader();
	void setVec3(const std::string & name, const glm::vec3 & value) const;
	void setVec3(const std::string & name, float x, float y, float z) const;
	void setVec4(const std::string & name, const glm::vec4 & value) const;
	void setVec4(const std::string & name, float x, float y, float z, float w);
	void setMat2(const std::string & name, const glm::mat2 & mat) const;
	void setMat3(const std::string & name, const glm::mat3 & mat) const;
	void setMat4(const std::string & name, const glm::mat4 & mat) const;
};

#endif /* Shader_hpp */
