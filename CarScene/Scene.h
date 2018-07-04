

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "OpenGL.h"

#include "Shader.h"

#include "Box.h"
#include "FrustumPyramid.h"
#include "Cylinder.h"
#include "FrustumCone.h"
#include "Car.h"
#include "House.h"
#include "Lamp.h"

using namespace glm;

class Scene
{
public:

	Car* car; // moving one

	Scene(Shader *shader);
	~Scene();

	void Draw();
	void Update(bool *keys, GLfloat deltaTime);

private:
	mat4 noParentModel;

	// parts of the scene
	Box* ground;
	Box* asphalt1;
	Box* grass1;

	House* house1;
	House* house2;
	House* house3;

	Car* car2; // static one

	Box* wall1;
	Box* wall2;
	Box* wall3;
	Box* wall4;
	Box* wall5;
	Box* wall6;
	Box* wall7;
	Box* wall8;
	Box* wall9;
	Box* wall10;

	Lamp* lamp1;
	Lamp* lamp2;
	Lamp* lamp3;
	Lamp* lamp4;
};

