#include "Scene.h"



Scene::Scene(Shader *shader)
{
	 this->noParentModel = one<mat4>();
	 
	 this->ground = new Box(shader, vec3(0, 0, 0), vec3(20, 0.01, 20), vec3(0, 0, 0), TheTextureManager::Instance()->GetID("pavementBrick"), TheTextureManager::Instance()->GetID("pavementBrick"), TheTextureManager::Instance()->GetID("pavementBrick"), 20);
	 this->asphalt1 = new Box(shader, vec3(0, 0.01, 0.7), vec3(20, 0.01, 3), vec3(0, 0, 0), TheTextureManager::Instance()->GetID("asphalt"), TheTextureManager::Instance()->GetID("asphalt"), TheTextureManager::Instance()->GetID("asphalt"), 1);
	 this->grass1 = new Box(shader, vec3(4, 0, -6), vec3(12, 0.02, 8), vec3(0, 0, 0), TheTextureManager::Instance()->GetID("grass1"), TheTextureManager::Instance()->GetID("grass1"), TheTextureManager::Instance()->GetID("grass1"), 10);
	 
	 this->car = new Car(shader, vec3(0, 0, 0), vec3(1, 1, 1), vec3(0, 0, 0));
	 
	 this->house1 = new House(shader, vec3(8.5, 0, 7.5), vec3(1, 1, 1), vec3(0, 0, 0)); 
	 this->house2 = new House(shader, vec3(-7.5, 0, -8.5), vec3(1, 1, 1), vec3(0, 90, 0));
	 this->house3 = new House(shader, vec3(-5, 0, 5), vec3(1, 1, 1), vec3(0, 0, 0));
	 
	 this->wall1 = new Box(shader, vec3(-5.75, 1, 9.9), vec3(8.5, 2, 0.2), vec3(0, 0, 0), TheTextureManager::Instance()->GetID("brick1"), TheTextureManager::Instance()->GetID("brick1"), TheTextureManager::Instance()->GetID("brick1"), 2);
	 this->wall2 = new Box(shader, vec3(2.75, 1, 9.9), vec3(8.5, 2, 0.2), vec3(0, 0, 0), TheTextureManager::Instance()->GetID("brick1"), TheTextureManager::Instance()->GetID("brick1"), TheTextureManager::Instance()->GetID("brick1"), 2);
	 this->wall3 = new Box(shader, vec3(-1.25, 1, -9.9), vec3(7.5, 2, 0.2), vec3(0, 0, 0), TheTextureManager::Instance()->GetID("brick1"), TheTextureManager::Instance()->GetID("brick1"), TheTextureManager::Instance()->GetID("brick1"), 2);
	 this->wall4 = new Box(shader, vec3(6.25, 1, -9.9), vec3(7.5, 2, 0.2), vec3(0, 0, 0), TheTextureManager::Instance()->GetID("brick1"), TheTextureManager::Instance()->GetID("brick1"), TheTextureManager::Instance()->GetID("brick1"), 2);
	 this->wall5 = new Box(shader, vec3(9.9, 1, 2), vec3(0.2, 2, 8.0), vec3(0, 0, 0), TheTextureManager::Instance()->GetID("brick1"), TheTextureManager::Instance()->GetID("brick1"), TheTextureManager::Instance()->GetID("brick1"), 2);
	 this->wall6 = new Box(shader, vec3(9.9, 1, -6), vec3(0.2, 2, 8.0), vec3(0, 0, 0), TheTextureManager::Instance()->GetID("brick1"), TheTextureManager::Instance()->GetID("brick1"), TheTextureManager::Instance()->GetID("brick1"), 2);
	 this->wall7 = new Box(shader, vec3(-9.9, 1, 5.75), vec3(0.2, 2, 8.5), vec3(0, 0, 0), TheTextureManager::Instance()->GetID("brick1"), TheTextureManager::Instance()->GetID("brick1"), TheTextureManager::Instance()->GetID("brick1"), 2);
	 this->wall8 = new Box(shader, vec3(-9.9, 1, -2.75), vec3(0.2, 2, 8.5), vec3(0, 0, 0), TheTextureManager::Instance()->GetID("brick1"), TheTextureManager::Instance()->GetID("brick1"), TheTextureManager::Instance()->GetID("brick1"), 2);
	 
	 this->wall9 = new Box(shader, vec3(7.09, 0.7, 3.75), vec3(0.2, 1.4, 2.5), vec3(0, 0, 0), TheTextureManager::Instance()->GetID("hedge1"), TheTextureManager::Instance()->GetID("hedge1"), TheTextureManager::Instance()->GetID("hedge1"), 1); 
	 this->wall10 = new Box(shader, vec3(-8, 0.7, -4.6), vec3(4, 1.4, 0.2), vec3(0, 0, 0), TheTextureManager::Instance()->GetID("hedge2"), TheTextureManager::Instance()->GetID("hedge2"), TheTextureManager::Instance()->GetID("hedge2"), 1); 
	 
	 this->car2 = new Car(shader, vec3(-8, 0, -5.6), vec3(1, 1, 1), vec3(0, 0, 0));

	 this->lamp1 = new Lamp(shader, vec3(5.0, 0.0, 2.5), vec3(1.0, 1.0, 1.0), vec3(0.0, 180.0, 0.0));
	 this->lamp2 = new Lamp(shader, vec3(-8.0, 0.0, 2.5), vec3(1.0, 1.0, 1.0), vec3(0.0, 180.0, 0.0));
	 this->lamp3 = new Lamp(shader, vec3(-5.0, 0.0, -1.0), vec3(1.0, 1.0, 1.0), vec3(0.0, 0.0, 0.0));
	 this->lamp4 = new Lamp(shader, vec3(8.5, 0.0, -9.0), vec3(1.0, 1.0, 1.0), vec3(0.0, 0.0, 0.0));
}


Scene::~Scene()
{
	 this->ground->~Box();
	 this->asphalt1->~Box();
	 this->grass1->~Box();

	 this->car->~Car();
	 
	 this->house1->~House();
	 this->house2->~House();
	 this->house3->~House();
	 
	 this->wall1->~Box();
	 this->wall2->~Box();
	 this->wall3->~Box();
	 this->wall4->~Box();
	 this->wall5->~Box();
	 this->wall6->~Box();
	 this->wall7->~Box();
	 this->wall8->~Box();
	 this->wall9->~Box();
	 this->wall10->~Box();

	 this->car->~Car();

	 this->lamp1->~Lamp();
	 this->lamp2->~Lamp();
	 this->lamp3->~Lamp();
	 this->lamp4->~Lamp();
}

void Scene::Draw()
{
	this->ground->Draw(noParentModel);
	this->asphalt1->Draw(noParentModel);
	this->grass1->Draw(noParentModel);
	 
	this->car->Draw();
	 
	this->house1->Draw();
	this->house2->Draw();
	this->house3->Draw();
	 
	this->wall1->Draw(noParentModel);
	this->wall2->Draw(noParentModel);
	this->wall3->Draw(noParentModel);
	this->wall4->Draw(noParentModel);
	this->wall5->Draw(noParentModel);
	this->wall6->Draw(noParentModel);
	this->wall7->Draw(noParentModel);
	this->wall8->Draw(noParentModel);
	this->wall9->Draw(noParentModel);
	this->wall10->Draw(noParentModel);

	this->car2->Draw();

	this->lamp1->Draw();
	this->lamp2->Draw();
	this->lamp3->Draw();
	this->lamp4->Draw();
}


void Scene::Update(bool *keys, GLfloat deltaTime)
{	
	car->ProcessInputKeys(keys, deltaTime);

	bool overlapCarHouse1 = car->Overlap(house1);
	bool overlapCarHouse2 = car->Overlap(house2);
	bool overlapCarHouse3 = car->Overlap(house3);
	bool overlapCarCar2 = car->Overlap(car2);
	bool overlapCarWall1 = car->Overlap(wall1);
	bool overlapCarWall2 = car->Overlap(wall2);
	bool overlapCarWall3 = car->Overlap(wall3);
	bool overlapCarWall4 = car->Overlap(wall4);
	bool overlapCarWall5 = car->Overlap(wall5);
	bool overlapCarWall6 = car->Overlap(wall6);
	bool overlapCarWall7 = car->Overlap(wall7);
	bool overlapCarWall8 = car->Overlap(wall8);
	bool overlapCarWall9 = car->Overlap(wall9);
	bool overlapCarWall10 = car->Overlap(wall10);
	bool overlapCarLamp1 = car->Overlap(lamp1);
	bool overlapCarLamp2 = car->Overlap(lamp2);
	bool overlapCarLamp3 = car->Overlap(lamp3);
	bool overlapCarLamp4 = car->Overlap(lamp4);

	if (
		overlapCarHouse1 ||
		overlapCarHouse2 ||
		overlapCarHouse3 ||

		overlapCarCar2 ||

		overlapCarWall1 ||
		overlapCarWall2 ||
		overlapCarWall3 ||
		overlapCarWall4 ||
		overlapCarWall5 ||
		overlapCarWall6 ||
		overlapCarWall7 ||
		overlapCarWall8 ||
		overlapCarWall9 ||
		overlapCarWall10 ||
		overlapCarLamp1 ||
		overlapCarLamp2 ||
		overlapCarLamp3 ||
		overlapCarLamp4
		)
	{
		car->ProcessInputKeysBack(keys, deltaTime);
	}
}