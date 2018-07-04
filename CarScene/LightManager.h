
#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "OpenGL.h"

#include "Shader.h"

#include "Singleton.h"

using  namespace glm;

class LightManager
{
public:
	// set initial light parameters
	void InitLightValues(int pointLightAmount, int spotLightAmount, vec3* spotLightPositions, vec3* spotLightDirections);
	// set light parameters in the shader variables
	void SetLightParamsInShader(Shader *shader);

	void Restart();

	// update spot light on every move or rotation of the car
	void UpdateSpotLight(int spotLightAmount, vec3* spotLightPositions, vec3* spotLightDirections);
	// color to clear the scene every time main loop begins
	vec4 ClearColor;

private:

	// right now not used - e.g. size of arrays should be base on them
	int pointLightAmount, spotLightAmount;

	// Directional light
	vec3 dirLightDirection;
	vec4 dirLightAmbient;
	vec4 dirLightDiffuse;
	vec4 dirLightSpecular;
	// Point lights
	vec3 pointLightPosition[4];
	vec4 pointLightAmbient[4];
	vec4 pointLightDiffuse[4];
	vec4 pointLightSpecular[4];
	float pointLightConstant[4];
	float pointLightLinear[4];
	float pointLightQuadratic[4];

	// SpotLight
	vec3 spotLightPosition[2];
	vec3 spotLightDirection[2];
	vec4 spotLightAmbient[2];
	vec4 spotLightDiffuse[2];
	vec4 spotLightSpecular[2];
	float spotLightConstant[2];
	float spotLightLinear[2];
	float spotLightQuadratic[2];
	float spotLightCutOff[2];
	float spotLightOuterCutOff[2];
};

typedef Singleton<LightManager> TheLightManager;