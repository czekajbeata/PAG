#include "Texture.h"
#include <stb_image.h>


Texture::Texture()
{
	GLuint texture = NULL;
	bool loaded = tryToLoadTexture(texture);
	if (loaded) activateTexture(texture);
}

Texture::~Texture()
{
}

bool Texture::tryToLoadTexture(GLuint& texture)
{
	bool isLoaded;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// ustaw opcje zawijania/filtrowania tekstury (na aktywnym obiekcie tekstury)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// za�aduj obraz i wygeneruj obiekt tekstury
	int width, height, nrChannels;
	unsigned char *data = stbi_load("wall.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		isLoaded = true;
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
		isLoaded = false;
	}
	stbi_image_free(data);


	return isLoaded;
}

void Texture::activateTexture(GLuint texture)
{
	glBindTexture(GL_TEXTURE_2D, texture);
}
