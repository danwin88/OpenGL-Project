#include "House.h"

House::House() {}
// BoundingBoxa size = vec3(0, 0, 0) means theat it must be calculated as fittted to the size of car
House::House(Shader* shader, vec3 pos, vec3 size, vec3 rotAngleDeg)
	: House(shader, pos, size, rotAngleDeg, vec3(0, 0, 0), vec3(0, 0, 0), vec3(0, 0, 0))
{ }
House::House(Shader* shader, vec3 pos, vec3 size, vec3 rotAngleDeg, vec3 bbPos, vec3 bbSize, vec3 bbRotAngleDeg)
{
	this->shader = shader;
	this->pos = pos;
	this->size = size;
	this->rotAngleDeg = rotAngleDeg;

	// BoundingBoxa size = vec3(0, 0, 0) means theat it must be calculated as fittted to the size of car
	CreateModel(bbPos, bbSize, bbRotAngleDeg);
}
House::~House()
{

}

// grip point: center of XZ, Y on the ground level
void House::CreateModel(vec3 bbPos, vec3 bbSize, vec3 bbRotAngleDeg)
{
	this->boundingBox = new BoundingBox(bbPos, bbSize, bbRotAngleDeg);
	if (bbSize == vec3(0, 0, 0))
	{
		this->boundingBox = new BoundingBox(vec3(0, 0, 0), vec3(1, 1, 1), vec3(0, 0, 0));
		UpdateBoundingBox();
	}

	this->base = new Box( shader, vec3(0, 1.5, 0),	vec3(3, 3, 5),	vec3(0, 0, 0), TheTextureManager::Instance()->GetID("house1"), TheTextureManager::Instance()->GetID("house2"), TheTextureManager::Instance()->GetID("brick1"), 1);
	this->roof = new FrustumPyramid( shader, vec3(0, 3.75, 0),	vec3(3.6, 1.5, 6.5),	vec3(0, 0, 0), TheTextureManager::Instance()->GetID("roofTiles"), TheTextureManager::Instance()->GetID("roofTiles"), TheTextureManager::Instance()->GetID("roofTiles"), 1, 0.5, 1);

	UpdateHouseModel();
}

void House::Move(vec3 pos)
{
	this->pos += pos;
	UpdateHouseModel();
}
void House::Resize(vec3 size)
{
	this->size += size;
	UpdateHouseModel();
}
void House::Rotate(vec3 rotAngleDeg)
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

	UpdateHouseModel();
}

void House::Draw()
{
	this->base->Draw(this->houseModel);
	this->roof->Draw(this->houseModel);
}

void House::UpdateHouseModel()
{
	houseModel = mat4();
	houseModel = translate(houseModel, this->pos);
	houseModel = rotate(houseModel, radians(this->rotAngleDeg.x), vec3(1, 0, 0));
	houseModel = rotate(houseModel, radians(this->rotAngleDeg.y), vec3(0, 1, 0));
	houseModel = rotate(houseModel, radians(this->rotAngleDeg.z), vec3(0, 0, 1));
	houseModel = scale(houseModel, this->size);

	UpdateBoundingBox();
}

void House::UpdateBoundingBox()
{
	vec3 basePos = vec3(0, 3, 0);
	vec3 baseSize = vec3(4.0, 6, 4.0);
	vec3 baseRotAngleDeg = vec3(0, 0, 0);

	vec3 transformedPos = basePos + this->pos;
	vec3 transformedSize = baseSize * this->size;
	vec3 transformedRotAngleDeg = baseRotAngleDeg + this->rotAngleDeg;

	this->boundingBox->UpdateBoundingBox(transformedPos, transformedSize, transformedRotAngleDeg);
}