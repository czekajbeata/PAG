#include "Shader.h"

Shader::Shader()
{
	shaderProgram = glCreateProgram();
	if (shaderProgram == 0)
	{
		fprintf(stderr, "Error creating program object.\n");
	}

	/* Shader load from file and compile */
	loadAndCompileShader(GL_VERTEX_SHADER, "Shaders/basic.vert", shaderProgram);
	loadAndCompileShader(GL_FRAGMENT_SHADER, "Shaders/basic.frag", shaderProgram);
	glLinkProgram(shaderProgram);

	// sprawdzenie linkowania programu zawieraj¹cego vertex shader i fragment shader
	checkLinkingProgram(shaderProgram);
}

Shader::~Shader()
{
}

std::string Shader::loadShader(std::string fileName)
{
	std::string filetext;
	std::string line;
	std::ifstream inFile(fileName);

	if (!inFile)
	{
		fprintf(stderr, "Could not open file %s", fileName.c_str());
		inFile.close();

		return NULL;
	}
	else
	{
		while (inFile.good())
		{
			getline(inFile, line);
			filetext.append(line + "\n");
		}

		inFile.close();

		return filetext;
	}
}

void Shader::loadAndCompileShader(GLint shaderType, std::string fileName, GLuint & shaderProgram)
{
	GLuint shaderObject = glCreateShader(shaderType);

	 if (shaderObject == 0)
	{
		fprintf(stderr, "Error creating %s.\n", fileName.c_str());
		return;
	} 

	std::string shaderCodeString = loadShader(fileName);

	if (shaderCodeString.empty())
	{
		printf("Shader code is empty! Shader name %s\n", fileName.c_str());
		return;
	}

	const char * shaderCode = shaderCodeString.c_str();
	const GLint codeSize = shaderCodeString.size();

	glShaderSource(shaderObject, 1, &shaderCode, &codeSize);
	glCompileShader(shaderObject);

	GLint result;
	checkCompilingShader(shaderObject, fileName, result);

	if (result) 
	{
		glAttachShader(shaderProgram, shaderObject);
		glDeleteShader(shaderObject);
	}
}

void Shader::checkLinkingProgram(GLuint shaderProgram)
{
	GLint status;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);

	if (status == GL_FALSE)
	{
		fprintf(stderr, "Failed to link shader program!\n");

		GLint logLen;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &logLen);

		if (logLen > 0)
		{
			char* log = (char*)malloc(logLen);
			GLsizei written;
			glGetProgramInfoLog(shaderProgram, logLen, &written, log);

			fprintf(stderr, "Program log: \n%s", log);
			free(log);
		}
	}
}

void Shader::checkCompilingShader(GLuint shaderObject, std::string fileName, GLint& result)
{

	glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		fprintf(stderr, "%s compilation failed!\n", fileName.c_str());

		GLint logLen;
		glGetShaderiv(shaderObject, GL_INFO_LOG_LENGTH, &logLen);

		if (logLen > 0)
		{
			char * log = (char *)malloc(logLen);

			GLsizei written;
			glGetShaderInfoLog(shaderObject, logLen, &written, log);

			fprintf(stderr, "Shader log: \n%s", log);
			free(log);
		}

		return;
	}
}

void Shader::activateShaderProgram(GLuint shaderProgram)
{
	glUseProgram(shaderProgram);
}
