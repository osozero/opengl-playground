#include "Texture.h"
#include <stb_image/stb_image.h>
#include <iostream>

Texture::Texture(const GLchar* imagePath, GLenum imageChannel)
{
	loadImage(imagePath, imageChannel);
}

void Texture::AddTexture(const GLchar* imagePath, GLenum imageChannel, int textureIndex)
{
	loadImage(imagePath, imageChannel, textureIndex);
}

Texture::~Texture()
{
}

void Texture::BindTexture(int textureIndex)
{
	glBindTexture(GL_TEXTURE_2D, IDs.at(textureIndex));
}

void Texture::ActivateTexture(GLenum textureIndex)
{
	glActiveTexture(textureIndex);
}

void Texture::loadImage(const GLchar* imagePath, GLenum imageChannel, int textureIndex)
{
	if(imageChannel==GL_RGBA)
	{
		stbi_set_flip_vertically_on_load(true);
	}

	const auto imageData = stbi_load(imagePath, &width, &height, &nrChannels, 0);
	unsigned int id;
	if (imageData)
	{
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);

		IDs.push_back(id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, imageChannel, GL_UNSIGNED_BYTE, imageData);
	}
	else
	{
		std::cout << "Image could not be loaded" << std::endl;
	}

	stbi_image_free(imageData);
}
