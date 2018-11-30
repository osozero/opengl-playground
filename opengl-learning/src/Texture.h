#pragma once
#include <glad/glad.h>
#include <vector>

class Texture
{
public:
	std::vector<unsigned int> IDs{};
	Texture() =delete;
	Texture(const GLchar * imagePath,GLenum imageChannel);
	void AddTexture(const GLchar *imagePath, GLenum imageChannel,int textureIndex);
	~Texture();
	void BindTexture(int textureIndex);
	void ActivateTexture(GLenum textureIndex);
private:
	int width{}, height{}, nrChannels{};
	void loadImage(const GLchar* imagePath, GLenum imageChannel, int textureIndex = 0);
};

