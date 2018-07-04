

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
#include "FrustumPyramid.h"
#include "Cylinder.h"
#include "FrustumCone.h"
#include "House.h"
#include "TextureManager.h"

class House
{
private:
	// position, size and angle of rotatiion ( in degrees, for each of axis separatelly )
	vec3 pos, size, rotAngleDeg;
	// model matrix
	mat4 houseModel;
	// shader used for drawing
	Shader *shader;

	// -------- parts of the house
	Box* base;
	FrustumPyramid* roof;

	void CreateModel(vec3 bbPos, vec3 bbSize, vec3 bbRotAngleDeg);
	void UpdateBoundingBox();
	//------------

public:
	// bounding box used for checking collision of this house - by default calculated based on size and position of its components ( base, roof rtc )
	BoundingBox *boundingBox;

	House();
	House(Shader* shader, vec3 pos, vec3 size, vec3 rotAngleDeg);
	House(Shader* shader, vec3 pos, vec3 size, vec3 rotAngleDeg, vec3 bbPos, vec3 bbSize, vec3 bbRotAngleDeg);
	~House();

	// mvoe this house by given vector ( not used )
	void Move(vec3 pos);
	// resize this house - on each axis as many times as given size ( not used )
	void Resize(vec3 size);
	// rotate this house by given angle - for each axis separatelly
	void Rotate(vec3 rotAngleDeg);
	// set new position, size, angle of rotatiion ( in degrees, for each of axis separatelly ), then updates BoundingBox
	void UpdateHouseModel();
	// drawing this house
	void Draw();
};

