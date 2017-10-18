#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
class Shader
{
public:
	Shader();
	~Shader();
	GLuint shaderProgram = NULL;
	void activateShaderProgram(GLuint shaderProgram);
	
private:
	std::string loadShader(std::string fileName);
	void loadAndCompileShader(GLint shaderType, std::string fileName, GLuint& shaderProgram);
	void checkLinkingProgram(GLuint shaderProgram);
	void checkCompilingShader(GLuint shaderObject, std::string fileName, GLint& result);

};




