


#pragma once

#include <string>
#include <map>

#include "OpenGL.h"

#include "Singleton.h"

#include "Shader.h"
#include "ScreenManager.h"
#include "TextureManager.h"

// FreeType
#include <ft2build.h>
#include FT_FREETYPE_H
// https ://learnopengl.com/#!In-Practice/Text-Rendering
// https://www.freetype.org/download.html
// RUN: freetype-2.3.5-1-setup.exe
// 2 lines added in Include in Project/Properties:  C:\Program Files (x86)\GnuWin32\include   C:\Program Files (x86)\GnuWin32\include\freetype2
// 1 line added in lub in Project/Properties   C:\Program Files (x86)\GnuWin32\lib
// above: #pragma comment( lib, "freetype.lib" )

using namespace glm;

struct Character {
	GLuint TextureID;   // ID handle of the glyph texture
	glm::ivec2 Size;    // Size of glyph
	glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
	GLuint Advance;    // Horizontal offset to advance to next glyph
};

class TextManager
{
public:
	void Init();
	void PrepareBeforeRenderText(Shader *fontShader);
	void CleanAfterRenderText();
	void RenderText(Shader &shader, string text, GLfloat x, GLfloat y, GLfloat scale, vec3 color);
	void Restart();

private:
	map<GLchar, Character> Characters;
	GLuint fontVAO, fontVBO;
	int fontTextureUnitId = GL_TEXTURE31;	// last available
	int fontTextureId = 31;					// last available
};

typedef Singleton<TextManager> TheTextManager;