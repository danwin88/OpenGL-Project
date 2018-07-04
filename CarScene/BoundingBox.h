

#pragma once

#include "OpenGL.h"

using namespace glm;

// Box using for checking collision witj OBB algorithm
class BoundingBox
{
public:
	BoundingBox(vec3 pos, vec3 size, vec3 rotAngleDeg);
	~BoundingBox();

	// set new position, size, angle of rotatiion ( in degrees, for each of axis separatelly )
	void UpdateBoundingBox(vec3 pos, vec3 size, vec3 rotAngleDeg);
	// check if this boundingBox is overlapped with the one given as parameter - call OBBOverlap method
	bool Overlap(BoundingBox* box);

private:
	vec3 pos, size;
	mat4 rotateMatrix;

	// the OBB algorithm
	// here ( in OBBOverlap method ) size means length from center to corner
	// in Box class size means length of the edge
	bool OBBOverlap(vec3 sizeA, vec3 posA, mat4 rotMatrixA, vec3 sizeB, vec3 posB, mat4 rotMatrixB);
};

