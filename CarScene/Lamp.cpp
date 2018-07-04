#include "Lamp.h"

Lamp::Lamp() {}
// BoundingBoxa size = vec3(0, 0, 0) means theat it must be calculated as fittted to the size of car
Lamp::Lamp(Shader* shader, vec3 pos, vec3 size, vec3 rotAngleDeg)
	: Lamp(shader, pos, size, rotAngleDeg, vec3(0, 0, 0), vec3(0, 0, 0), vec3(0, 0, 0))
{ }
Lamp::Lamp(Shader* shader, vec3 pos, vec3 size, vec3 rotAngleDeg, vec3 bbPos, vec3 bbSize, vec3 bbRotAngleDeg)
{
	this->shader = shader;
	this->pos = pos;
	this->size = size;
	this->rotAngleDeg = rotAngleDeg;

	// BoundingBoxa size = vec3(0, 0, 0) means theat it must be calculated as fittted to the size of car
	CreateModel(bbPos, bbSize, bbRotAngleDeg);
}
Lamp::~Lamp()
{

}


// grip point: center of XZ, Y on the ground level
void Lamp::CreateModel(vec3 bbPos, vec3 bbSize, vec3 bbRotAngleDeg)
{
	// BoundingBoxa size = vec3(0, 0, 0) means theat it must be calculated as fittted to the size of car
	this->boundingBox = new BoundingBox(bbPos, bbSize, bbRotAngleDeg);
	if (bbSize == vec3(0, 0, 0))
	{
		this->boundingBox = new BoundingBox(vec3(0, 0, 0), vec3(1, 1, 1), vec3(0, 0, 0));
		UpdateBoundingBox();
	}

	this->base = new FrustumCone(shader, vec3(0, 1.5, 0), vec3(0.15, 3, 0.15), vec3(0, 0, 0), TheTextureManager::Instance()->GetID("metal1"), TheTextureManager::Instance()->GetID("metal2"), 0.7);
	this->top = new FrustumPyramid(shader, vec3(0, 3.05, 0.24), vec3(0.4, 0.1, 0.6), vec3(0, 0, 0), TheTextureManager::Instance()->GetID("metal1"), TheTextureManager::Instance()->GetID("metal1"), TheTextureManager::Instance()->GetID("metal2"), 0.5, 0.5, 1);

	UpdateHouseModel();
}

void Lamp::Move(vec3 pos)
{
	this->pos += pos;
	UpdateHouseModel();
}
void Lamp::Resize(vec3 size)
{
	this->size += size;
	UpdateHouseModel();
}
void Lamp::Rotate(vec3 rotAngleDeg)
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

void Lamp::Draw()
{
	this->base->Draw(this->houseModel);
	this->top->Draw(this->houseModel);
}

void Lamp::UpdateHouseModel()
{
	houseModel = mat4();
	houseModel = translate(houseModel, this->pos);
	houseModel = rotate(houseModel, radians(this->rotAngleDeg.x), vec3(1, 0, 0));
	houseModel = rotate(houseModel, radians(this->rotAngleDeg.y), vec3(0, 1, 0));
	houseModel = rotate(houseModel, radians(this->rotAngleDeg.z), vec3(0, 0, 1));
	houseModel = scale(houseModel, this->size);

	UpdateBoundingBox();
}

void Lamp::UpdateBoundingBox()
{
	vec3 basePos = vec3(0, 1.55, 0);
	vec3 baseSize = vec3(0.15, 3.1, 0.15);
	vec3 baseRotAngleDeg = vec3(0, 0, 0);

	vec3 transformedPos = basePos + this->pos;
	vec3 transformedSize = baseSize * this->size;
	vec3 transformedRotAngleDeg = baseRotAngleDeg + this->rotAngleDeg;

	this->boundingBox->UpdateBoundingBox(transformedPos, transformedSize, transformedRotAngleDeg);
}