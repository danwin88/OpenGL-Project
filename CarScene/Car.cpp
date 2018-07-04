#include "Car.h"

Car::Car() {}

// BoundingBoxa size = vec3(0, 0, 0) means theat it must be calculated as fittted to the size of car
Car::Car(Shader* shader, vec3 pos, vec3 size, vec3 rotAngleDeg)
	: Car(shader, pos, size, rotAngleDeg, vec3(0, 0, 0), vec3(0, 0, 0), vec3(0, 0, 0))
{ }

Car::Car(Shader* shader, vec3 pos, vec3 size, vec3 rotAngleDeg, vec3 bbPos, vec3 bbSize, vec3 bbRotAngleDeg)
{
	this->shader = shader;
	this->pos = pos;
	this->size = size;
	this->rotAngleDeg = rotAngleDeg;

	// BoundingBoxa size = vec3(0, 0, 0) means theat it must be calculated as fittted to the size of car
	CreateModel(bbPos, bbSize, bbRotAngleDeg);
}

Car::~Car()
{
}

// grip point: center of XZ, Y on the asphalt level
void Car::CreateModel(vec3 bbPos, vec3 bbSize, vec3 bbRotAngleDeg)
{
	// BoundingBoxa size = vec3(0, 0, 0) means theat it must be calculated as fittted to the size of car
	this->boundingBox = new BoundingBox(bbPos, bbSize, bbRotAngleDeg);
	if (bbSize == vec3(0, 0, 0))
	{
		this->boundingBox = new BoundingBox(vec3(0, 0, 0), vec3(1, 1, 1), vec3(0, 0, 0));
		UpdateBoundingBox();
	}

	this->chasis1 = new FrustumPyramid(this->shader, vec3(0, 0.5, 0), vec3(2.9, 0.5, 1), vec3(0, 0, 0), TheTextureManager::Instance()->GetID("carBodySide"), TheTextureManager::Instance()->GetID("carBodySide"), TheTextureManager::Instance()->GetID("carBodyTop"), 0.05, 0.02, 1);
	this->body1 = new FrustumPyramid(this->shader, vec3(-0.2, 1.0, 0), vec3(1.8, 0.5, 1 - 0.02), vec3(0, 0, 0), TheTextureManager::Instance()->GetID("carBody"), TheTextureManager::Instance()->GetID("carBody"), TheTextureManager::Instance()->GetID("carBodyTop"), 0.3, 0.3, 1);
	this->body2 = new FrustumPyramid(this->shader, vec3(-0.2, 1.0, 0), vec3(0.05, 0.5, 1 - 0.018), vec3(0, 0, 0), TheTextureManager::Instance()->GetID("carBody2"), TheTextureManager::Instance()->GetID("carBody"), TheTextureManager::Instance()->GetID("carBodyTop"), 0.0, 0.3, 1);

	this->frontLeftWheel = new Cylinder(this->shader, vec3(0.7, 0.25, 0.45), vec3(0.25, 0.15, 0.25), vec3(90, 0, 0), TheTextureManager::Instance()->GetID("tyreFront"), TheTextureManager::Instance()->GetID("tyreSide"));
	this->frontRightWheel = new Cylinder(this->shader, vec3(0.7, 0.25, -0.45), vec3(0.25, 0.15, 0.25), vec3(90, 0, 0), TheTextureManager::Instance()->GetID("tyreFront"), TheTextureManager::Instance()->GetID("tyreSide"));
	this->rearLeftWheel = new Cylinder(this->shader, vec3(-1.0, 0.25, 0.45), vec3(0.25, 0.15, 0.25), vec3(90, 0, 0), TheTextureManager::Instance()->GetID("tyreFront"), TheTextureManager::Instance()->GetID("tyreSide"));
	this->rearRightWheel = new Cylinder(this->shader, vec3(-1.0, 0.25, -0.45), vec3(0.25, 0.15, 0.25), vec3(90, 0, 0), TheTextureManager::Instance()->GetID("tyreFront"), TheTextureManager::Instance()->GetID("tyreSide"));
	
	this->frontLeftLight = new Cylinder(this->shader, vec3(1.3, 0.5, 0.35), vec3(0.1, 0.3, 0.1), vec3(0, 0, 90), TheTextureManager::Instance()->GetID("lamp1"), TheTextureManager::Instance()->GetID("lamp1"));
	this->frontRightLight = new Cylinder(this->shader, vec3(1.3, 0.5, -0.35), vec3(0.1, 0.3, 0.1), vec3(0, 0, 90), TheTextureManager::Instance()->GetID("lamp1"), TheTextureManager::Instance()->GetID("lamp1"));
	this->rearLeftLight = new Cylinder(this->shader, vec3(-1.3, 0.5, 0.35), vec3(0.1, 0.3, 0.1), vec3(0, 0, 90), TheTextureManager::Instance()->GetID("lamp2"), TheTextureManager::Instance()->GetID("lamp2"));
	this->rearRightLight = new Cylinder(this->shader, vec3(-1.3, 0.5, -0.35), vec3(0.1, 0.3, 0.1), vec3(0, 0, 90), TheTextureManager::Instance()->GetID("lamp2"), TheTextureManager::Instance()->GetID("lamp2"));

	UpdateCarModel();
}

void Car::UpdateBoundingBox()
{
	vec3 basePos = vec3(0, 0.625, 0);
	vec3 baseSize = vec3(2.9, 1.225, 1);
	vec3 baseRotAngleDeg = vec3(0, 0, 0);

	vec3 transformedPos = basePos + this->pos;
	vec3 transformedSize = baseSize * this->size;
	vec3 transformedRotAngleDeg = baseRotAngleDeg + this->rotAngleDeg;

	this->boundingBox->UpdateBoundingBox(transformedPos, transformedSize, transformedRotAngleDeg);
}

void Car::Move(vec3 pos)
{
	this->pos += pos;
	UpdateCarModel();

	UpdateWheelsModel(pos);
}

void Car::Resize(vec3 size)
{
	this->size += size;
	UpdateCarModel();
}

void Car::Rotate(vec3 rotAngleDeg)
{
	this->rotAngleDeg += rotAngleDeg;
	if (this->rotAngleDeg.x > 360)
	{
		this->rotAngleDeg.x = this->rotAngleDeg.x - 360;
	}
	if (this->rotAngleDeg.y > 360)
	{
		this->rotAngleDeg.y = this->rotAngleDeg.y - 360;
	}
	if (this->rotAngleDeg.z > 360)
	{
		this->rotAngleDeg.z = this->rotAngleDeg.z - 360;
	}

	UpdateCarModel();
}

void Car::UpdateCarModel()
{
	carModel = mat4();
	carModel = translate(carModel, this->pos);
	carModel = rotate(carModel, radians(this->rotAngleDeg.x), vec3(1, 0, 0));
	carModel = rotate(carModel, radians(this->rotAngleDeg.y), vec3(0, 1, 0));
	carModel = rotate(carModel, radians(this->rotAngleDeg.z), vec3(0, 0, 1));
	carModel = scale(carModel, this->size);

	UpdateBoundingBox();
	CalculateSpecularLightProperties();
}

void Car::UpdateWheelsModel(vec3 pos)
{
	GLfloat rotateDirFromCarOrientation = -sign(cos(radians(rotAngleDeg.y)));
	this->frontLeftWheel->Rotate(vec3(0, rotateDirFromCarOrientation * (pos.x * defaultWheelRotateSpeed), 0));
	this->frontRightWheel->Rotate(vec3(0, rotateDirFromCarOrientation * (pos.x * defaultWheelRotateSpeed), 0));
	this->rearLeftWheel->Rotate(vec3(0, rotateDirFromCarOrientation * (pos.x * defaultWheelRotateSpeed), 0));
	this->rearRightWheel->Rotate(vec3(0, rotateDirFromCarOrientation * (pos.x * defaultWheelRotateSpeed), 0));
}

void Car::Draw()
{
	this->chasis1->Draw(this->carModel);
	this->body1->Draw(this->carModel);
	this->body2->Draw(this->carModel);

	this->frontLeftWheel->Draw(this->carModel);
	this->frontRightWheel->Draw(this->carModel);
	this->rearLeftWheel->Draw(this->carModel);
	this->rearRightWheel->Draw(this->carModel);

	this->frontLeftLight->Draw(this->carModel);
	this->frontRightLight->Draw(this->carModel);
	this->rearLeftLight->Draw(this->carModel);
	this->rearRightLight->Draw(this->carModel);
}


bool Car::Overlap(House* house)
{
	return this->boundingBox->Overlap(house->boundingBox);
}
bool Car::Overlap(Box* box)
{
	return this->boundingBox->Overlap(box->boundingBox);
}
bool Car::Overlap(Car* car)
{
	return this->boundingBox->Overlap(car->boundingBox);
}
bool Car::Overlap(Lamp* lamp)
{
	return this->boundingBox->Overlap(lamp->boundingBox);
}

void Car::ProcessInputKeys(bool *keys, GLfloat deltaTime)
{
	if (!keys[GLFW_KEY_LEFT_SHIFT])
	{
		GLfloat moveSpeed = defaultMoveSpeed * deltaTime;
		GLfloat rotatespeed = defaultRotateSpeed * deltaTime;

		if (keys[GLFW_KEY_LEFT_CONTROL])
		{
			moveSpeed *= 2;
			rotatespeed *= 2;
		}

		// move
		// FRONY
		if (keys[GLFW_KEY_W])
		{
			this->Move(vec3(moveSpeed * cos(radians(rotAngleDeg.y)), 0, -moveSpeed * sin(radians(rotAngleDeg.y))));
		}
		// BACK
		if (keys[GLFW_KEY_S])
		{
			this->Move(vec3(-moveSpeed * cos(radians(rotAngleDeg.y)), 0, moveSpeed * sin(radians(rotAngleDeg.y))));
		}
		// rotate
		// LEFT
		if (keys[GLFW_KEY_A])
		{
			this->Rotate(vec3(0, rotatespeed, 0));
		}
		// RIGHT
		if (keys[GLFW_KEY_D])
		{
			this->Rotate(vec3(0, -rotatespeed, 0));
		}
	}
}

void Car::ProcessInputKeysBack(bool *keys, GLfloat deltaTime)
{
	if (!keys[GLFW_KEY_LEFT_SHIFT])
	{
		GLfloat moveSpeed = defaultMoveSpeed * deltaTime;
		GLfloat rotatespeed = defaultRotateSpeed * deltaTime;

		if (keys[GLFW_KEY_LEFT_CONTROL])
		{
			moveSpeed *= 2;
			rotatespeed *= 2;
		}

		// move
		// FRONY
		if (keys[GLFW_KEY_W])
		{
			this->Move(vec3(-moveSpeed * cos(radians(rotAngleDeg.y)), 0, moveSpeed * sin(radians(rotAngleDeg.y))));
		}
		// BACK
		if (keys[GLFW_KEY_S])
		{
			this->Move(vec3(moveSpeed * cos(radians(rotAngleDeg.y)), 0, -moveSpeed * sin(radians(rotAngleDeg.y))));
		}
		// rotate
		// LEFT
		if (keys[GLFW_KEY_A])
		{
			this->Rotate(vec3(0, -rotatespeed, 0));
		}
		// RIGHT
		if (keys[GLFW_KEY_D])
		{
			this->Rotate(vec3(0, rotatespeed, 0));
		}
	}
}

// the position of the specular light is placed on fron reflectors and moves whec the car is moved
// dirForLeftSpecularLight and dirForRightSpecularLight are calculated ( in 2D - OY does not change ) based on rotAngleDeg
void Car::CalculateSpecularLightProperties()
{
	this->posForLeftSpecularLight = this->pos + vec3(1.0, 0.0, -0.5);
	this->dirForLeftSpecularLight.x = cos(radians(this->rotAngleDeg.y));
	this->dirForLeftSpecularLight.y = pos.y;
	this->dirForLeftSpecularLight.z = -sin(radians(this->rotAngleDeg.y));

	this->posForRightSpecularLight = this->pos + vec3(1.0, 0.0, 0.5);
	this->dirForRightSpecularLight.x = cos(radians(this->rotAngleDeg.y));
	this->dirForRightSpecularLight.y = pos.y;
	this->dirForRightSpecularLight.z = -sin(radians(this->rotAngleDeg.y));
}