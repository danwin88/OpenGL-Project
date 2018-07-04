

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

class Cylinder
{
protected:
	// position, size and angle of rotatiion ( in degrees, for each of axis separatelly )
	vec3 pos, size, rotAngleDeg;
	// Vertex Buffer Objext and Vertex Array Object - used by shader to keep vertices
	GLuint VBO, VAO;
	// model matrix
	mat4 model;
	// shader used for drawing
	Shader *shader;
	// location in memory ( belongs to shader ) of model variable
	GLint modelLoc;

	// id of texture for side of the cylinder and its base
	int sideTextureId, baseTextureId;

	static const int defNumOfTrianglesOnCircle = 20;

	// update "model" matrix using pos, size and rotAngleDeg
	void UpdateModel();

	void GenerateCircle(GLfloat* retArray, int numOfTrianglesOnCircle, int offset, float y);

public:
	// bounding box used for checking collision of this cylinder - by default equals to this cylinder size and pos - but could be different if needed
	BoundingBox *boundingBox;

	// default ctor used to create auto arrays
	Cylinder::Cylinder();
	Cylinder(Shader* shader, vec3 pos, vec3 size, vec3 rotAngleDeg, int sideTextureId, int baseTextureId);
	Cylinder(Shader* shader, vec3 pos, vec3 size, vec3 rotAngleDeg, int sideTextureId, int baseTextureId, vec3 bbPos, vec3 bbSize, vec3 bbRotAngleDeg);
	~Cylinder();

	// mvoe this cylinder by given vector
	void Move(vec3 pos);
	// resize this cylinder - on each axis as many times as given size
	void Resize(vec3 size);
	// rotate this cylinder by given angle - for each axis separatelly
	void Rotate(vec3 rotAngleDeg);
	// drawing this cylinder - translate to world coordinates by multiplying by parentModel matrix
	virtual void Draw(mat4 parentModel);

	// check if this cylinder collide with the box given as parameter - call its bounding box Overlap method
	bool Overlap(Box* box);
	// check if this cylinder collide with another cylinder given as parameter - call its bounding box Overlap method
	bool Overlap(Cylinder* cylinder);
};
