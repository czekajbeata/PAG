﻿#include "Texture.h"
#include "Const.h"

#include <stb_image.h>
#include <iostream>

Texture::Texture(const std::string& pTexturePath) : mTexturePath(pTexturePath)
{
	glGenTextures(1, &mTexture); //Generowanie kontenera na tekstury

	try
	{
		loadTexture(pTexturePath);
	}
	catch (std::runtime_error err)
	{
		throw err;
	}
}

Texture::Texture(const Texture& pSourceTexture) :Texture(pSourceTexture.mTexturePath) {}

Texture::~Texture()
{
	glDeleteTextures(1, &mTexture);
}

void Texture::loadTexture(const std::string& pTexturePath)
{
	int width, height, numberOfChannels;
	GLuint imageDepth;

	//stbi_set_flip_vertically_on_load(true); //Obrócenie obrazu przed załadowaniem
	unsigned char* textureData = stbi_load(pTexturePath.c_str(), &width, &height, &numberOfChannels, 0);
	if (textureData)
	{
		if (numberOfChannels == 4) imageDepth = GL_RGBA; //W przypadku gdy obrazek jest 4 kanałowy, tekstura będzie RGBA
		else if (numberOfChannels == 3) imageDepth = GL_RGB;
		else imageDepth = GL_RED;
		glBindTexture(GL_TEXTURE_2D, mTexture);
		//Parametry dla wczytanej tekstury
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST); //Pomniejszenie tekstury, bierze najbliższą mipmapę i interpoluje liniowo
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //Powiększenie tekstury, interpoluje liniowo

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //Tekstura S - zawija
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //Tekstura T - zawija
		glTexImage2D(GL_TEXTURE_2D,
			0, //Stopnie mipmappingu
			imageDepth, //Wewnętrzny format teksela
			width, height, //Szerokośc i wysokość obrazka
			0, //Kontur??
			imageDepth, //Format danych obrazka
			GL_UNSIGNED_BYTE, //Typ danych obrazka
			textureData);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(textureData);
	}
	else throw std::runtime_error("(Texture::loadTexture): Błąd odczytu pliku");
}

void Texture::deselectAllTextures()
{
	int i = 0;
	for (i = 0; i<31; i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, NULL);
	}
}

void Texture::selectActiveTexture(const std::string& pTextureType, const unsigned int& pTextureNumber)
{
	if (pTextureNumber >= MAXIMUM_NUMBER_OF_TEXTURES_PER_TYPE) std::runtime_error("(Texture::selectActiveTexture): Numer tekstury jest większy od dopuszczalnej ilości tekstur");
	if (pTextureType.compare(DIFFUSE_NAME) == 0)
	{
		glActiveTexture(GL_TEXTURE0 + pTextureNumber);
	}
	else if (pTextureType.compare(SPECULAR_NAME) == 0)
	{
		glActiveTexture(GL_TEXTURE0 + SPECULAR_STARTING_INDEX + pTextureNumber);
	}
	else if (pTextureType.compare(NORMAL_NAME) == 0)
	{
		glActiveTexture(GL_TEXTURE0 + NORMAL_STARTING_INDEX + pTextureNumber);
	}
	glBindTexture(GL_TEXTURE_2D, mTexture);
}

const std::string& Texture::getTexturePath() { return mTexturePath; }
