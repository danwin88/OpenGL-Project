
#pragma once

#include "OpenGL.h"

#include "Shader.h"
#include "BoundingBox.h"
#include "FrustumPyramid.h"
#include "FrustumCone.h"
#include "TextureManager.h"


class Lamp
{
private:
	// position, size and angle of rotatiion ( in degrees, for each of axis separatelly )
	vec3 pos, size, rotAngleDeg;
	// model matrix
	mat4 houseModel;
	// shader used for drawing
	Shader *shader;

	// -------- parts of the lamp
	FrustumCone* base;
	FrustumPyramid* top;
	//------------

	// creates all above parts of car from basic objects ( cones, pyramids etc )
	void CreateModel(vec3 bbPos, vec3 bbSize, vec3 bbRotAngleDeg);
	// set new position, size, angle of rotatiion ( in degrees, for each of axis separatelly )
	void UpdateBoundingBox();

public:
	// bounding box used for checking collision of this lamp - by default calculated based on size and position of its components ( base, top rtc )
	BoundingBox *boundingBox;

	Lamp();
	Lamp(Shader* shader, vec3 pos, vec3 size, vec3 rotAngleDeg);
	Lamp(Shader* shader, vec3 pos, vec3 size, vec3 rotAngleDeg, vec3 bbPos, vec3 bbSize, vec3 bbRotAngleDeg);
	~Lamp();

	// mvoe this lamp by given vector ( not used )
	void Move(vec3 pos);
	// resize this lamp - on each axis as many times as given size ( not used )
	void Resize(vec3 size);
	// rotate this lamp by given angle - for each axis separatelly
	void Rotate(vec3 rotAngleDeg);
	// set new position, size, angle of rotatiion ( in degrees, for each of axis separatelly ), then updates BoundingBox
	void UpdateHouseModel();
	// drawing this lamp
	void Draw();
};

