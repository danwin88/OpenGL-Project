#include "LightManager.h"


void LightManager::InitLightValues(int pointLightAmount, int spotLightAmount, vec3* spotLightPositions, vec3* spotLightDirections)
{
	this->pointLightAmount = pointLightAmount;
	this->spotLightAmount = spotLightAmount;


	// Directional light
	dirLightDirection = vec3(-0.5f, -1.0f, -0.5f);
	dirLightAmbient = vec4(0.05f, 0.05f, 0.05f, 1);
	dirLightDiffuse = vec4(1.0f, 1.0f, 1.0f, 1);
	//dirLightSpecular = vec4(0.5f, 0.5f, 0.5f, 1);
	dirLightSpecular = vec4(0.0f, 0.0f, 0.0f, 1);

	// Point Light 1
	pointLightPosition[0] = vec3(5.0, 2.9, 2.2);
	pointLightAmbient[0] = vec4(0.05f, 0.05f, 0.05f, 1);
	pointLightDiffuse[0] = vec4(1.0f, 1.0f, 0.0f, 1);
	pointLightSpecular[0] = vec4(1.0f, 1.0f, 1.0f, 1);
	pointLightConstant[0] = 1.0f;
	pointLightLinear[0] = 0.09f;
	pointLightQuadratic[0] = 0.032f;
	// Point Light 2
	pointLightPosition[1] = vec3(-8.0, 2.9, 2.2);
	pointLightAmbient[1] = vec4(0.05f, 0.05f, 0.05f, 1);
	pointLightDiffuse[1] = vec4(1.0f, 1.0f, 0.0f, 1);
	pointLightSpecular[1] = vec4(1.0f, 1.0f, 1.0f, 1);
	pointLightConstant[1] = 1.0f;
	pointLightLinear[1] = 0.09f;
	pointLightQuadratic[1] = 0.032f;
	// Point Light 3
	pointLightPosition[2] = vec3(-5.0, 2.9, -0.7);
	pointLightAmbient[2] = vec4(0.05f, 0.05f, 0.05f, 1);
	pointLightDiffuse[2] = vec4(1.0f, 1.0f, 0.0f, 1);
	pointLightSpecular[2] = vec4(1.0f, 1.0f, 1.0f, 1);
	pointLightConstant[2] = 1.0f;
	pointLightLinear[2] = 0.09f;
	pointLightQuadratic[2] = 0.032f;
	// Point Light 4
	pointLightPosition[3] = vec3(9.0, 2.9, -8.2);
	pointLightAmbient[3] = vec4(0.05f, 0.05f, 0.05f, 1);
	pointLightDiffuse[3] = vec4(0.0f, 0.0f, 1.0f, 1);
	pointLightSpecular[3] = vec4(1.0f, 1.0f, 1.0f, 1);
	pointLightConstant[3] = 1.0f;
	pointLightLinear[3] = 0.09f;
	pointLightQuadratic[3] = 0.032f;

	// Spot Light 1
	spotLightPosition[0] = spotLightPositions[0];
	spotLightDirection[0] = spotLightDirections[0];
	spotLightAmbient[0] = vec4(0.0f, 0.0f, 0.0f, 1);
	spotLightDiffuse[0] = vec4(1.0f, 1.0f, 1.0f, 1);
	spotLightSpecular[0] = vec4(1.0f, 1.0f, 1.0f, 1);
	spotLightConstant[0] = 1.0f;
	spotLightLinear[0] = 0.09;
	spotLightQuadratic[0] = 0.032;
	spotLightCutOff[0] = cos(radians(12.5f));
	spotLightOuterCutOff[0] = cos(radians(15.0f));
	// Spot Light 2
	spotLightPosition[1] = spotLightPositions[1];
	spotLightDirection[1] = spotLightDirections[1];
	spotLightAmbient[1] = vec4(0.0f, 0.0f, 0.0f, 1);
	spotLightDiffuse[1] = vec4(1.0f, 1.0f, 1.0f, 1);
	spotLightSpecular[1] = vec4(1.0f, 1.0f, 1.0f, 1);
	spotLightConstant[1] = 1.0f;
	spotLightLinear[1] = 0.09;
	spotLightQuadratic[1] = 0.032;
	spotLightCutOff[1] = cos(radians(12.5f));
	spotLightOuterCutOff[1] = cos(radians(15.0f));


	this->ClearColor = dirLightAmbient;
}


void LightManager::UpdateSpotLight(int spotLightAmount, vec3* spotLightPositions, vec3* spotLightDirections)
{
	for (int i = 0; i < spotLightAmount; i++)
	{
		spotLightPosition[i] = spotLightPositions[i];
		spotLightDirection[i] = spotLightDirections[i];
	}
}


void LightManager::SetLightParamsInShader(Shader *shader)
{
	glUniform3f(glGetUniformLocation(shader->Program, "dirLight.direction"), dirLightDirection.x, dirLightDirection.y, dirLightDirection.z);
	glUniform4f(glGetUniformLocation(shader->Program, "dirLight.ambient"), dirLightAmbient.x, dirLightAmbient.y, dirLightAmbient.z, dirLightAmbient.a);
	glUniform4f(glGetUniformLocation(shader->Program, "dirLight.diffuse"), dirLightDiffuse.x, dirLightDiffuse.y, dirLightDiffuse.z, dirLightDiffuse.a);
	glUniform4f(glGetUniformLocation(shader->Program, "dirLight.specular"), dirLightSpecular.x, dirLightSpecular.y, dirLightSpecular.z, dirLightSpecular.a);
	// Point light 1
	glUniform3f(glGetUniformLocation(shader->Program, "pointLights[0].position"), pointLightPosition[0].x, pointLightPosition[0].y, pointLightPosition[0].z);
	glUniform4f(glGetUniformLocation(shader->Program, "pointLights[0].ambient"), pointLightAmbient[0].x, pointLightAmbient[0].y, pointLightAmbient[0].z, pointLightAmbient[0].a);
	glUniform4f(glGetUniformLocation(shader->Program, "pointLights[0].diffuse"), pointLightDiffuse[0].x, pointLightDiffuse[0].y, pointLightDiffuse[0].z, pointLightDiffuse[0].a);
	glUniform4f(glGetUniformLocation(shader->Program, "pointLights[0].specular"), pointLightSpecular[0].x, pointLightSpecular[0].y, pointLightSpecular[0].z, pointLightSpecular[0].a);
	glUniform1f(glGetUniformLocation(shader->Program, "pointLights[0].constant"), pointLightConstant[0]);
	glUniform1f(glGetUniformLocation(shader->Program, "pointLights[0].linear"), pointLightLinear[0]);
	glUniform1f(glGetUniformLocation(shader->Program, "pointLights[0].quadratic"), pointLightQuadratic[0]);
	// Point light 2
	glUniform3f(glGetUniformLocation(shader->Program, "pointLights[1].position"), pointLightPosition[1].x, pointLightPosition[1].y, pointLightPosition[1].z);
	glUniform4f(glGetUniformLocation(shader->Program, "pointLights[1].ambient"), pointLightAmbient[1].x, pointLightAmbient[1].y, pointLightAmbient[1].z, pointLightAmbient[1].a);
	glUniform4f(glGetUniformLocation(shader->Program, "pointLights[1].diffuse"), pointLightDiffuse[1].x, pointLightDiffuse[1].y, pointLightDiffuse[1].z, pointLightDiffuse[1].a);
	glUniform4f(glGetUniformLocation(shader->Program, "pointLights[1].specular"), pointLightSpecular[1].x, pointLightSpecular[1].y, pointLightSpecular[1].z, pointLightSpecular[1].a);
	glUniform1f(glGetUniformLocation(shader->Program, "pointLights[1].constant"), pointLightConstant[1]);
	glUniform1f(glGetUniformLocation(shader->Program, "pointLights[1].linear"), pointLightLinear[1]);
	glUniform1f(glGetUniformLocation(shader->Program, "pointLights[1].quadratic"), pointLightQuadratic[1]);
	// Point light 3
	glUniform3f(glGetUniformLocation(shader->Program, "pointLights[2].position"), pointLightPosition[2].x, pointLightPosition[2].y, pointLightPosition[2].z);
	glUniform4f(glGetUniformLocation(shader->Program, "pointLights[2].ambient"), pointLightAmbient[2].x, pointLightAmbient[2].y, pointLightAmbient[2].z, pointLightAmbient[2].a);
	glUniform4f(glGetUniformLocation(shader->Program, "pointLights[2].diffuse"), pointLightDiffuse[2].x, pointLightDiffuse[2].y, pointLightDiffuse[2].z, pointLightDiffuse[2].a);
	glUniform4f(glGetUniformLocation(shader->Program, "pointLights[2].specular"), pointLightSpecular[2].x, pointLightSpecular[2].y, pointLightSpecular[2].z, pointLightSpecular[2].a);
	glUniform1f(glGetUniformLocation(shader->Program, "pointLights[2].constant"), pointLightConstant[2]);
	glUniform1f(glGetUniformLocation(shader->Program, "pointLights[2].linear"), pointLightLinear[2]);
	glUniform1f(glGetUniformLocation(shader->Program, "pointLights[2].quadratic"), pointLightQuadratic[2]);
	// Point light 4
	glUniform3f(glGetUniformLocation(shader->Program, "pointLights[3].position"), pointLightPosition[3].x, pointLightPosition[3].y, pointLightPosition[3].z);
	glUniform4f(glGetUniformLocation(shader->Program, "pointLights[3].ambient"), pointLightAmbient[3].x, pointLightAmbient[3].y, pointLightAmbient[3].z, pointLightAmbient[3].a);
	glUniform4f(glGetUniformLocation(shader->Program, "pointLights[3].diffuse"), pointLightDiffuse[3].x, pointLightDiffuse[3].y, pointLightDiffuse[3].z, pointLightDiffuse[3].a);
	glUniform4f(glGetUniformLocation(shader->Program, "pointLights[3].specular"), pointLightSpecular[3].x, pointLightSpecular[3].y, pointLightSpecular[3].z, pointLightSpecular[3].a);
	glUniform1f(glGetUniformLocation(shader->Program, "pointLights[3].constant"), pointLightConstant[3]);
	glUniform1f(glGetUniformLocation(shader->Program, "pointLights[3].linear"), pointLightLinear[3]);
	glUniform1f(glGetUniformLocation(shader->Program, "pointLights[3].quadratic"), pointLightQuadratic[3]);
	// SpotLight 1
	glUniform3f(glGetUniformLocation(shader->Program, "spotLight[0].position"), spotLightPosition[0].x, spotLightPosition[0].y, spotLightPosition[0].z);
	glUniform3f(glGetUniformLocation(shader->Program, "spotLight[0].direction"), spotLightDirection[0].x, spotLightDirection[0].y, spotLightDirection[0].z);
	glUniform4f(glGetUniformLocation(shader->Program, "spotLight[0].ambient"), spotLightAmbient[0].x, spotLightAmbient[0].y, spotLightAmbient[0].z, spotLightAmbient[0].a);
	glUniform4f(glGetUniformLocation(shader->Program, "spotLight[0].diffuse"), spotLightDiffuse[0].x, spotLightDiffuse[0].y, spotLightDiffuse[0].z, spotLightDiffuse[0].a);
	glUniform4f(glGetUniformLocation(shader->Program, "spotLight[0].specular"), spotLightSpecular[0].x, spotLightSpecular[0].y, spotLightSpecular[0].z, spotLightSpecular[0].a);
	glUniform1f(glGetUniformLocation(shader->Program, "spotLight[0].constant"), spotLightConstant[0]);
	glUniform1f(glGetUniformLocation(shader->Program, "spotLight[0].linear"), spotLightLinear[0]);
	glUniform1f(glGetUniformLocation(shader->Program, "spotLight[0].quadratic"), spotLightQuadratic[0]);
	glUniform1f(glGetUniformLocation(shader->Program, "spotLight[0].cutOff"), spotLightCutOff[0]);
	glUniform1f(glGetUniformLocation(shader->Program, "spotLight[0].outerCutOff"), spotLightOuterCutOff[0]);
	// SpotLight 2
	glUniform3f(glGetUniformLocation(shader->Program, "spotLight[1].position"), spotLightPosition[1].x, spotLightPosition[1].y, spotLightPosition[1].z);
	glUniform3f(glGetUniformLocation(shader->Program, "spotLight[1].direction"), spotLightDirection[1].x, spotLightDirection[1].y, spotLightDirection[1].z);
	glUniform4f(glGetUniformLocation(shader->Program, "spotLight[1].ambient"), spotLightAmbient[1].x, spotLightAmbient[1].y, spotLightAmbient[1].z, spotLightAmbient[1].a);
	glUniform4f(glGetUniformLocation(shader->Program, "spotLight[1].diffuse"), spotLightDiffuse[1].x, spotLightDiffuse[1].y, spotLightDiffuse[1].z, spotLightDiffuse[1].a);
	glUniform4f(glGetUniformLocation(shader->Program, "spotLight[1].specular"), spotLightSpecular[1].x, spotLightSpecular[1].y, spotLightSpecular[1].z, spotLightSpecular[1].a);
	glUniform1f(glGetUniformLocation(shader->Program, "spotLight[1].constant"), spotLightConstant[1]);
	glUniform1f(glGetUniformLocation(shader->Program, "spotLight[1].linear"), spotLightLinear[1]);
	glUniform1f(glGetUniformLocation(shader->Program, "spotLight[1].quadratic"), spotLightQuadratic[1]);
	glUniform1f(glGetUniformLocation(shader->Program, "spotLight[1].cutOff"), spotLightCutOff[1]);
	glUniform1f(glGetUniformLocation(shader->Program, "spotLight[1].outerCutOff"), spotLightOuterCutOff[1]);

	// Set material properties
	glUniform1f(glGetUniformLocation(shader->Program, "material.shininess"), 256.0f);
}

void LightManager::Restart()
{

}