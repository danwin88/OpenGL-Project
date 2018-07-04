
#pragma once

// Include GLEW
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "OpenGL.h"

class Shader
{
public:
	GLuint Program;

	// creates the shader instance based on text files ( passed as arguments ) containing code for vertext shader and fragment shader
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

	// make this shader current ( active )
	void Use();
};

