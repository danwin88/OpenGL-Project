


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
#include "Lamp.h"

#include "BoundingBox.h"
#include "TextureManager.h"

#include <iostream>

using namespace glm;

class Car
{
private:
	GLfloat defaultMoveSpeed = 2;
	GLfloat defaultWheelRotateSpeed = 300;
	GLfloat defaultRotateSpeed = 30;

	// position, size and angle of rotatiion ( in degrees, for each of axis separatelly )
	vec3 pos, size, rotAngleDeg;

	// model matrix
	mat4 carModel;
	// shader used for drawing
	Shader *shader;

	// -------- parts of the car
	FrustumPyramid* chasis1;
	FrustumPyramid* body1;
	FrustumPyramid* body2;

	Cylinder* frontLeftWheel;
	Cylinder* frontRightWheel;
	Cylinder* rearLeftWheel;
	Cylinder* rearRightWheel;
	Cylinder* frontLeftLight;
	Cylinder* frontRightLight;
	Cylinder* rearLeftLight;
	Cylinder* rearRightLight;
	//------------

	// creates all above parts of car from basic objects ( boxes, cylinders etc )
	void CreateModel(vec3 bbPos, vec3 bbSize, vec3 bbRotAngleDeg);
	// this method rotate car wheels when car is moved
	void UpdateWheelsModel(vec3 pos);
	// set new position, size, angle of rotatiion ( in degrees, for each of axis separatelly )
	void UpdateBoundingBox();


	void CalculateSpecularLightProperties();
public:
	// bounding box used for checking collision of this car - by default calculated based on size and position of its components ( chasis, body rtc )
	BoundingBox *boundingBox;

	// used to set up position and firection of two specular light ( fron reflectors ) of the car
	vec3 posForLeftSpecularLight;
	vec3 dirForLeftSpecularLight;
	vec3 posForRightSpecularLight;
	vec3 dirForRightSpecularLight;

	Car();
	Car(Shader* shader, vec3 pos, vec3 size, vec3 rotAngleDeg);
	Car(Shader* shader, vec3 pos, vec3 size, vec3 rotAngleDeg, vec3 bbPos, vec3 bbSize, vec3 bbRotAngleDeg);
	~Car();

	// mvoe this car by given vector
	void Move(vec3 pos);
	// resize this car - on each axis as many times as given size ( not used )
	void Resize(vec3 size);
	// rotate this car by given angle - for each axis separatelly
	void Rotate(vec3 rotAngleDeg);

	// set new position, size, angle of rotatiion ( in degrees, for each of axis separatelly ), then updates BoundingBox and calculates SpecularLight properties
	void UpdateCarModel();
	// drawing this car
	void Draw();

	// overriden methods to check collision with many kind of objects
	bool Overlap(House* box);
	bool Overlap(Box* box);
	bool Overlap(Car* box);
	bool Overlap(Lamp* lamp);

	// method to proces pressed keys ( result in moving or rotating car ) - called from Scene::Update
	void ProcessInputKeys(bool *keys, GLfloat deltaTime);
	// if there is collision the car must be moved back - and this is what below method does - it is invert to above one
	void ProcessInputKeysBack(bool *keys, GLfloat deltaTime);
};

