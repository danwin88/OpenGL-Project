

#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "OpenGL.h"

#include "Shader.h"
#include "BoundingBox.h"
#include "Box.h"

using namespace glm;

// inherit from Box - very few changes
class FrustumPyramid : public Box
{
private:
	/// How many to cut of in percentage ( from 0 to 1.0 )
	GLfloat oxCutOff;
	/// How many to cut of in percentage ( from 0 to 1.0 )
	GLfloat	ozCutOff;
public:
	FrustumPyramid::FrustumPyramid(); 
	FrustumPyramid(Shader* shader, vec3 pos, vec3 size, vec3 rotAngleDeg, int oxTextureId, int oyTextureId, int ozTextureId, GLfloat oxCutOff, GLfloat ozCutOff, int textureRepeat);
	FrustumPyramid(Shader* shader, vec3 pos, vec3 size, vec3 rotAngleDeg, int oxTextureId, int oyTextureId, int ozTextureId, GLfloat oxCutOff, GLfloat ozCutOff, int textureRepeat, vec3 bbPos, vec3 bbSize, vec3 bbRotAngleDeg);

	void FrustumPyramid::Draw(mat4 parentModel);

	bool Overlap(FrustumPyramid* box);

};
