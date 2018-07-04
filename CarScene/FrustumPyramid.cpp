#include "FrustumPyramid.h"

FrustumPyramid::FrustumPyramid() {}

FrustumPyramid::FrustumPyramid(Shader* shader, vec3 pos, vec3 size, vec3 rotAngleDeg, int oxTextureId, int oyTextureId, int ozTextureId, GLfloat oxCutOff, GLfloat ozCutOff, int textureRepeat)
	: FrustumPyramid(shader, pos, size, rotAngleDeg, oxTextureId, oyTextureId, ozTextureId, oxCutOff, ozCutOff, textureRepeat, pos, size, rotAngleDeg)
{	}

FrustumPyramid::FrustumPyramid(Shader* shader, vec3 pos, vec3 size, vec3 rotAngleDeg, int oxTextureId, int oyTextureId, int ozTextureId,  GLfloat oxCutOff, GLfloat ozCutOff, int textureRepeat, vec3 bbPos, vec3 bbSize, vec3 bbRotAngleDeg)
{
	this->boundingBox = new BoundingBox(bbPos, bbSize, bbRotAngleDeg);
	
	this->shader = shader;
	
	this->pos = pos;
	this->size = size;
	this->rotAngleDeg = rotAngleDeg;
	
	this->UpdateModel();
	
	this->modelLoc = glGetUniformLocation(this->shader->Program, "model");
	
	this->oxTextureId = oxTextureId;
	this->oyTextureId = oyTextureId;
	this->ozTextureId = ozTextureId;
	this->textureRepeat = textureRepeat;

	this->oxCutOff = oxCutOff;
	this->ozCutOff = ozCutOff;

	GLfloat oxCutOffHalf = this->oxCutOff / 2.0;
	GLfloat ozCutOffHalf = this->ozCutOff / 2.0;

	GLfloat boxVertices[] = {
		// Positions													// Normals											// Texture Coords
		// OZ FRONT
		-0.5f,						-0.5f,	-0.5f,						0.0f,	0.0f,		-1.0f,							0.0f,								0.0f,
		0.5f,						-0.5f,	-0.5f,						0.0f,	0.0f,		-1.0f,							textureRepeat,						0.0f,
		0.5f * (1.0 - oxCutOff),	0.5f,	-0.5f * (1.0 - ozCutOff),	0.0f,	(ozCutOffHalf),	-(1.0 - ozCutOffHalf),		(textureRepeat - oxCutOffHalf),		textureRepeat,
		0.5f * (1.0 - oxCutOff),	0.5f,	-0.5f * (1.0 - ozCutOff),	0.0f,	(ozCutOffHalf),	-(1.0 - ozCutOffHalf),		(textureRepeat - oxCutOffHalf),		textureRepeat,
		-0.5f * (1.0 - oxCutOff),	0.5f,	-0.5f * (1.0 - ozCutOff),	0.0f,	(ozCutOffHalf),	-(1.0 - ozCutOffHalf),		(oxCutOffHalf),						textureRepeat,
		-0.5f,						-0.5f,	-0.5f,						0.0f,	0.0f,		-1.0f,							0.0f,								0.0f,
		// OZ BACK - default camera looks at it
		-0.5f,						-0.5f,	0.5f,						0.0f,	0.0f,		1.0f,							0.0f,								0.0f,
		0.5f,						-0.5f,  0.5f,						0.0f,	0.0f,		1.0f,							textureRepeat,						0.0f,
		0.5f * (1.0 - oxCutOff),	0.5f,	0.5f * (1.0 - ozCutOff),	0.0f,	(ozCutOffHalf),	(1.0 - ozCutOffHalf),		(textureRepeat - oxCutOffHalf),		textureRepeat,
		0.5f * (1.0 - oxCutOff),	0.5f,	0.5f * (1.0 - ozCutOff),	0.0f,	(ozCutOffHalf),	(1.0 - ozCutOffHalf),		(textureRepeat - oxCutOffHalf),		textureRepeat,
		-0.5f * (1.0 - oxCutOff),	0.5f,	0.5f * (1.0 - ozCutOff),	0.0f,	(ozCutOffHalf),	(1.0 - ozCutOffHalf),		(oxCutOffHalf),						textureRepeat,
		-0.5f,						-0.5f,	0.5f,						0.0f,	0.0f,		1.0f,							0.0f,								0.0f,
		// OX LEFT
		-0.5f * (1.0 - oxCutOff),	0.5f,	0.5f * (1.0 - ozCutOff),	-(1.0 - oxCutOffHalf),	(oxCutOffHalf),	0.0f,		(textureRepeat - ozCutOffHalf),		textureRepeat,
		-0.5f * (1.0 - oxCutOff),	0.5f,	-0.5f * (1.0 - ozCutOff),	-(1.0 - oxCutOffHalf),	(oxCutOffHalf),	0.0f,		(ozCutOffHalf),						textureRepeat,
		-0.5f,						-0.5f,	-0.5f,						-1.0f,				0.0f,		0.0f,				0.0f,								0.0f,
		-0.5f,						-0.5f,	-0.5f,						-1.0f,				0.0f,		0.0f,				0.0f,								0.0f,
		-0.5f,						-0.5f,	0.5f,						-1.0f,				0.0f,		0.0f,				textureRepeat,						0.0f,
		-0.5f * (1.0 - oxCutOff),	0.5f,	0.5f * (1.0 - ozCutOff),	-(1.0 - oxCutOffHalf),	(oxCutOffHalf),	0.0f,		(textureRepeat - ozCutOffHalf),		textureRepeat,
		// OX RIGHT
		0.5f * (1.0 - oxCutOff),	0.5f,	0.5f * (1.0 - ozCutOff),	(1.0 - oxCutOffHalf),	(oxCutOffHalf),	0.0f,		(textureRepeat - ozCutOffHalf),		textureRepeat,
		0.5f * (1.0 - oxCutOff),	0.5f,	-0.5f * (1.0 - ozCutOff),	(1.0 - oxCutOffHalf),	(oxCutOffHalf),	0.0f,		(ozCutOffHalf),						textureRepeat,
		0.5f,						-0.5f,	-0.5f,						1.0f,				0.0f,		0.0f,				0.0f,								0.0f,
		0.5f,						-0.5f,	-0.5f,						1.0f,				0.0f,		0.0f,				0.0f,								0.0f,
		0.5f,						-0.5f,	0.5f,						1.0f,				0.0f,		0.0f,				textureRepeat,						0.0f,
		0.5f * (1.0 - oxCutOff),	0.5f,	0.5f * (1.0 - ozCutOff),	(1.0 - oxCutOffHalf),	(oxCutOffHalf),	0.0f,		(textureRepeat - ozCutOffHalf),		textureRepeat,
		// OY BOTTOM
		-0.5f,						-0.5f,	-0.5f,						0.0f,	-1.0f,	0.0f,								0.0f,								textureRepeat,
		0.5f,						-0.5f,	-0.5f,						0.0f,	-1.0f,  0.0f,								textureRepeat,						textureRepeat,
		0.5f,						-0.5f,	0.5f,						0.0f,	-1.0f,  0.0f,								textureRepeat,						0.0f,
		0.5f,						-0.5f,	0.5f,						0.0f,	-1.0f,  0.0f,								textureRepeat,						0.0f,
		-0.5f,						-0.5f,  0.5f,						0.0f,	-1.0f,	0.0f,								0.0f,								0.0f,
		-0.5f,						-0.5f, -0.5f,						0.0f,	-1.0f,	0.0f,								0.0f,								textureRepeat,
		// OY TOP
		-0.5f * (1.0 - oxCutOff),	0.5f,	-0.5f * (1.0 - ozCutOff),	0.0f,	1.0f,	0.0f,								0.0f,								textureRepeat,
		0.5f * (1.0 - oxCutOff),	0.5f,	-0.5f * (1.0 - ozCutOff),	0.0f,	1.0f,	0.0f,								textureRepeat,						textureRepeat,
		0.5f * (1.0 - oxCutOff),	0.5f,	0.5f * (1.0 - ozCutOff),	0.0f,	1.0f,	0.0f,								textureRepeat,						0.0f,
		0.5f * (1.0 - oxCutOff),	0.5f,	0.5f * (1.0 - ozCutOff),	0.0f,	1.0f,	0.0f,								textureRepeat,						0.0f,
		-0.5f * (1.0 - oxCutOff),	0.5f,	0.5f * (1.0 - ozCutOff),	0.0f,	1.0f,	0.0f,								0.0f,								0.0f,
		-0.5f * (1.0 - oxCutOff),	0.5f,	-0.5f * (1.0 - ozCutOff),	0.0f,	1.0f,	0.0f,								0.0f,								textureRepeat
	};

	glGenVertexArrays(1, &boxVAO);
	glGenBuffers(1, &boxVBO);
	
	glBindVertexArray(boxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, boxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 288, boxVertices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);
}


void FrustumPyramid::Draw(mat4 parentModel)
{
	mat4 worldMatrix = parentModel * model;

	glBindVertexArray(boxVAO);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(worldMatrix));

		glUniform1i(glGetUniformLocation(this->shader->Program, "material.diffuse"), this->oxTextureId);
		glDrawArrays(GL_TRIANGLES, 0, 12);

		glUniform1i(glGetUniformLocation(this->shader->Program, "material.diffuse"), this->oyTextureId);
		glDrawArrays(GL_TRIANGLES, 12, 12);

		glUniform1i(glGetUniformLocation(this->shader->Program, "material.diffuse"), this->ozTextureId);
		glDrawArrays(GL_TRIANGLES, 24, 12);
	glBindVertexArray(0);
}


bool FrustumPyramid::Overlap(FrustumPyramid* box)
{
	return this->boundingBox->Overlap(box->boundingBox);
}
