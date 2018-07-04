


#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "OpenGL.h"

#include "Shader.h"
#include "BoundingBox.h"

using namespace glm;

class Box
{
protected:
	// position, size and angle of rotatiion ( in degrees, for each of axis separatelly )
	vec3 pos, size, rotAngleDeg;
	// Vertex Buffer Objext and Vertex Array Object - used by shader to keep vertices
	GLuint boxVBO, boxVAO;
	// model matrix
	mat4 model;
	// shader used for drawing
	Shader *shader;
	// location in memory ( belongs to shader ) of model variable
	GLint modelLoc;

	// id of texture for each side of the box
	int oxTextureId, ozTextureId, oyTextureId;
	// how many times repeat texture on box
	int textureRepeat;

	// update "model" matrix using pos, size and rotAngleDeg
	void UpdateModel();

public:
	// bounding box used for checking collision of this box - by default equals to this box size and pos - but could be different if needed
	BoundingBox *boundingBox;

	// default ctor used to create auto arrays
	Box::Box();
	Box(Shader* shader, vec3 pos, vec3 size, vec3 rotAngleDeg, int oxTextureId, int oyTextureId, int ozTextureId, int textureRepeat);
	Box(Shader* shader, vec3 pos, vec3 size, vec3 rotAngleDeg, int oxTextureId, int oyTextureId, int ozTextureId, int textureRepeat, vec3 bbPos, vec3 bbSize, vec3 bbRotAngleDeg);
	~Box();

	// mvoe this box by given vector
	void Move(vec3 pos);
	// resize this box - on each axis as many times as given size
	void Resize(vec3 size);
	// rotate this box by given angle - for each axis separatelly
	void Rotate(vec3 rotAngleDeg);
	// drawing this box - translate to world coordinates by multiplying by parentModel matrix
	virtual void Draw(mat4 parentModel);

	// check if this box collide with the one given as parameter - call its bounding box Overlap method
	bool Overlap(Box* box);

};
