
#pragma once

#include "OpenGL.h"

#include "Include/soil.h"

#include "Singleton.h"
#include <string>
#include <map>

class TextureManager
{
public:
	TextureManager();
	~TextureManager();
	GLuint GetID(string name);
	int LoadFromFile(char* filenameDif, string name);
	
	void Restart();

	int FirstFreeTextureUnitId() const { 
		return _currentTextureUnit - 1; 
	}

private:
	int _currentTextureIdOffset;
	int _currentTextureUnit;

	map <string, GLuint> textureMap;
};

typedef Singleton<TextureManager> TheTextureManager;