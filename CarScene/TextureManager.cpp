#include "TextureManager.h"



TextureManager::TextureManager()
{
	this->_currentTextureIdOffset = 0x84C0; // GL_TEXTURE0
	this->_currentTextureUnit = 0;
}


TextureManager::~TextureManager()
{
}

GLuint TextureManager::GetID(string name)
{
	return textureMap[name];
}

int TextureManager::LoadFromFile(char* filenameDif, string name)
{
	int width, height;
	unsigned char *imageDif; // width * height must be divsible by 16 !

	GLuint diffuseMap; // = (textureId + 1)

	// create texture buffer
	glGenTextures(1, &diffuseMap);

	// read texture file - use SOIL llibrary
	imageDif = SOIL_load_image(filenameDif, &width, &height, 0, SOIL_LOAD_RGBA);

	// set given texture unit active
	glActiveTexture(this->_currentTextureIdOffset++);

	glBindTexture(GL_TEXTURE_2D, diffuseMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageDif);
	glGenerateMipmap(GL_TEXTURE_2D);

	// set texture parameters: filters, minipaps, repetable, wrapping etc
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);

	// free resources used by SOIL to load texture
	SOIL_free_image_data(imageDif);

	// add textureID to map - thanks to it texture can be achieved by its name, not id
	textureMap[name] = (diffuseMap - 1);

	int currentTextureUnit = this->_currentTextureUnit;
	this->_currentTextureUnit += 1;
	return currentTextureUnit;
}

void TextureManager::Restart()
{
	this->_currentTextureIdOffset = 0x84C0; // GL_TEXTURE0
	this->_currentTextureUnit = 0;


	for (auto it = textureMap.begin();it != textureMap.end();it++)
	{
		glDeleteTextures(1, &(it->second));
	}

	textureMap.clear();
}