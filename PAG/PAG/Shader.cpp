#include "Shader.h"

Shader::Shader()
{
	if (shaderProgram == 0)
	{
		fprintf(stderr, "Error creating program object.\n");
	}

	/* Shader load from file and compile */
	loadAndCompileShaderFromFile(GL_VERTEX_SHADER, "Shaders/basic.vert", shaderProgram);
	loadAndCompileShaderFromFile(GL_FRAGMENT_SHADER, "Shaders/basic.frag", shaderProgram);

	glLinkProgram(shaderProgram);

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

	////// 
	/*
	// vertex shader	
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// check for vertex shader compile errors 
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// fragment shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// check for fragment shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	} */

/*
	// link shaders
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader); */
}


Shader::~Shader()
{
}

std::string loadShader(std::string fileName)
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

void loadAndCompileShaderFromFile(GLint shaderType, std::string fileName, GLuint & shaderProgram)
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

	glAttachShader(shaderProgram, shaderObject);
	glDeleteShader(shaderObject);
}
