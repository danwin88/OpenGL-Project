


#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "OpenGL.h"

#include "Shader.h"
#include "BoundingBox.h"
#include "Cylinder.h"

// inherit from Cylinder - very few changes
class FrustumCone : public Cylinder
{
private:
	/// How many to cut of in percentage ( from 0 to 1.0 )
	GLfloat rCutOff;

protected:
	void GenerateCircle(GLfloat* retArray, int numOfTrianglesOnCircle, int offset, GLfloat y, GLfloat rCutOff);

public:
	FrustumCone();
	FrustumCone(Shader* shader, vec3 pos, vec3 size, vec3 rotAngleDeg, int diffuseTextureId, int specularTextureId, GLfloat rCutOff);
	FrustumCone(Shader* shader, vec3 pos, vec3 size, vec3 rotAngleDeg, int diffuseTextureId, int specularTextureId, GLfloat rCutOff, vec3 bbPos, vec3 bbSize, vec3 bbRotAngleDeg);

	void Draw(mat4 parentModel);

	bool Overlap(Cylinder* cylinder);
};

