#include "BoundingBox.h"


BoundingBox::BoundingBox(vec3 pos, vec3 size, vec3 rotAngleDeg)
{
	UpdateBoundingBox(pos, size, rotAngleDeg);
}


BoundingBox::~BoundingBox()
{
}


void BoundingBox::UpdateBoundingBox(vec3 pos, vec3 size, vec3 rotAngleDeg)
{
	this->pos = pos;
	this->size = size;

	this->rotateMatrix = one<mat4>();
	this->rotateMatrix = rotate(this->rotateMatrix, radians(rotAngleDeg.x), vec3(1, 0, 0));
	this->rotateMatrix = rotate(this->rotateMatrix, radians(rotAngleDeg.y), vec3(0, 1, 0));
	this->rotateMatrix = rotate(this->rotateMatrix, radians(rotAngleDeg.z), vec3(0, 0, 1));
}


bool BoundingBox::OBBOverlap(vec3 sizeA, vec3 posA, mat4 rotMatrixA, vec3 sizeB, vec3 posB, mat4 rotMatrixB)
{
	mat3 transformMatrixA3x3 = mat3(rotMatrixA);
	vec3 basisA[3];
	basisA[0] = column(transformMatrixA3x3, 0);
	basisA[1] = column(transformMatrixA3x3, 1);
	basisA[2] = column(transformMatrixA3x3, 2);

	mat3 transformMatrixB3x3 = mat3(rotMatrixB);
	vec3 basisB[3];
	basisB[0] = column(transformMatrixB3x3, 0);
	basisB[1] = column(transformMatrixB3x3, 1);
	basisB[2] = column(transformMatrixB3x3, 2);

	//translation, in parent frame
	vec3 v = posB - posA;
	//translation, in A's frame
	vec3 T(dot(v, basisA[0]), dot(v, basisA[1]), dot(v, basisA[2]));

	//B's basis with respect to A's local frame
	float R[3][3];
	float ra, rb, t;
	long i, k;

	//calculate rotation matrix
	for (i = 0; i < 3; i++)
	{
		for (k = 0; k < 3; k++)
		{
			R[i][k] = dot(basisA[i], (basisB[k]));
		}
	}
	// ALGORITHM: Use the separating axis test for all 15 potential separating axes. 
	// If a separating axis could not be found, the two boxes overlap. 

	//A's basis vectors
	for (i = 0; i < 3; i++)
	{
		ra = sizeA[i];
		rb = sizeB[0] * fabs(R[i][0]) + sizeB[1] * fabs(R[i][1]) + sizeB[2] * fabs(R[i][2]);
		t = fabs(T[i]);
		if (t > ra + rb)
		{
			return false;
		}
	}

	//B's basis vectors
	for (k = 0; k < 3; k++)
	{
		ra = sizeA[0] * fabs(R[0][k]) + sizeA[1] * fabs(R[1][k]) + sizeA[2] * fabs(R[2][k]);
		rb = sizeB[k];
		t = fabs(T[0] * R[0][k] + T[1] * R[1][k] + T[2] * R[2][k]);
		if (t > ra + rb)
		{
			return false;
		}
	}

	//9 cross products

	//L = A0 x B0
	ra = sizeA[1] * fabs(R[2][0]) + sizeA[2] * fabs(R[1][0]);
	rb = sizeB[1] * fabs(R[0][2]) + sizeB[2] * fabs(R[0][1]);
	t = fabs(T[2] * R[1][0] - T[1] * R[2][0]);
	if (t > ra + rb)
	{
		return false;
	}

	//L = A0 x B1
	ra = sizeA[1] * fabs(R[2][1]) + sizeA[2] * fabs(R[1][1]);
	rb = sizeB[0] * fabs(R[0][2]) + sizeB[2] * fabs(R[0][0]);
	t = fabs(T[2] * R[1][1] - T[1] * R[2][1]);
	if (t > ra + rb)
	{
		return false;
	}

	//L = A0 x B2
	ra = sizeA[1] * fabs(R[2][2]) + sizeA[2] * fabs(R[1][2]);
	rb = sizeB[0] * fabs(R[0][1]) + sizeB[1] * fabs(R[0][0]);
	t = fabs(T[2] * R[1][2] - T[1] * R[2][2]);
	if (t > ra + rb)
	{
		return false;
	}

	//L = A1 x B0
	ra = sizeA[0] * fabs(R[2][0]) + sizeA[2] * fabs(R[0][0]);
	rb = sizeB[1] * fabs(R[1][2]) + sizeB[2] * fabs(R[1][1]);
	t = fabs(T[0] * R[2][0] - T[2] * R[0][0]);
	if (t > ra + rb)
	{
		return false;
	}

	//L = A1 x B1
	ra = sizeA[0] * fabs(R[2][1]) + sizeA[2] * fabs(R[0][1]);
	rb = sizeB[0] * fabs(R[1][2]) + sizeB[2] * fabs(R[1][0]);
	t = fabs(T[0] * R[2][1] - T[2] * R[0][1]);
	if (t > ra + rb)
	{
		return false;
	}

	//L = A1 x B2
	ra = sizeA[0] * fabs(R[2][2]) + sizeA[2] * fabs(R[0][2]);
	rb = sizeB[0] * fabs(R[1][1]) + sizeB[1] * fabs(R[1][0]);
	t = fabs(T[0] * R[2][2] - T[2] * R[0][2]);
	if (t > ra + rb)
	{
		return false;
	}

	//L = A2 x B0
	ra = sizeA[0] * fabs(R[1][0]) + sizeA[1] * fabs(R[0][0]);
	rb = sizeB[1] * fabs(R[2][2]) + sizeB[2] * fabs(R[2][1]);
	t = fabs(T[1] * R[0][0] - T[0] * R[1][0]);
	if (t > ra + rb)
	{
		return false;
	}

	//L = A2 x B1
	ra = sizeA[0] * fabs(R[1][1]) + sizeA[1] * fabs(R[0][1]);
	rb = sizeB[0] * fabs(R[2][2]) + sizeB[2] * fabs(R[2][0]);
	t = fabs(T[1] * R[0][1] - T[0] * R[1][1]);
	if (t > ra + rb)
	{
		return false;
	}

	//L = A2 x B2
	ra = sizeA[0] * fabs(R[1][2]) + sizeA[1] * fabs(R[0][2]);
	rb = sizeB[0] * fabs(R[2][1]) + sizeB[1] * fabs(R[2][0]);
	t = fabs(T[1] * R[0][2] - T[0] * R[1][2]);
	if (t > ra + rb)
	{
		return false;
	}

	// no separating axis found, the two boxes overlap 
	return true;
}

bool BoundingBox::Overlap(BoundingBox* box)
{
	return OBBOverlap(0.5f * this->size, this->pos, this->rotateMatrix, 0.5f * box->size, box->pos, box->rotateMatrix);
}