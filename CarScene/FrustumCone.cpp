#include "FrustumCone.h"



FrustumCone::FrustumCone()
{ }

FrustumCone::FrustumCone(Shader* shader, vec3 pos, vec3 size, vec3 rotAngleDeg, int sideTextureId, int baseTextureId, GLfloat rCutOff)
	: FrustumCone(shader, pos, size, rotAngleDeg, sideTextureId, baseTextureId, rCutOff, pos, size, rotAngleDeg)
{ }

FrustumCone::FrustumCone(Shader* shader, vec3 pos, vec3 size, vec3 rotAngleDeg, int sideTextureId, int baseTextureId, GLfloat rCutOff, vec3 bbPos, vec3 bbSize, vec3 bbRotAngleDeg)
{
	this->boundingBox = new BoundingBox(bbPos, bbSize, bbRotAngleDeg);

	this->shader = shader;

	this->pos = pos;
	this->size = size;
	this->rotAngleDeg = rotAngleDeg;
	this->rCutOff = rCutOff;

	this->UpdateModel();

	this->modelLoc = glGetUniformLocation(this->shader->Program, "model");

	this->sideTextureId = sideTextureId;
	this->baseTextureId = baseTextureId;

	const int verticesAmount = (((defNumOfTrianglesOnCircle + 2) * 2 * 8) + ((defNumOfTrianglesOnCircle + 2) * 2 * 8));
	int verticesArraySize = sizeof(GLfloat) * verticesAmount;

	GLfloat vertices[verticesAmount];

	GLfloat y = 0.5f;

	// first circle
	GenerateCircle(vertices, defNumOfTrianglesOnCircle, 0, -y, 0);
	// second circle
	GenerateCircle(vertices, defNumOfTrianglesOnCircle, (defNumOfTrianglesOnCircle + 2) * 8, y, this->rCutOff);

	int offset = (defNumOfTrianglesOnCircle + 2) * 8 * 2;

	for (int i = 0; i < defNumOfTrianglesOnCircle + 2; i++)
	{
		vertices[i * 16 + offset + 0] = cos(i * 2 * pi<GLfloat>() / defNumOfTrianglesOnCircle) * (1.0 - this->rCutOff);
		vertices[i * 16 + offset + 1] = y;
		vertices[i * 16 + offset + 2] = sin(i * 2 * pi<GLfloat>() / defNumOfTrianglesOnCircle) * (1.0 - this->rCutOff);
		vertices[i * 16 + offset + 3] = cos(i * 2 * pi<GLfloat>() / defNumOfTrianglesOnCircle) * (1.0 - this->rCutOff);
		vertices[i * 16 + offset + 4] = 0;
		vertices[i * 16 + offset + 5] = sin(i * 2 * pi<GLfloat>() / defNumOfTrianglesOnCircle) * (1.0 - this->rCutOff);
		vertices[i * 16 + offset + 6] = i % 2;   // Tex
		vertices[i * 16 + offset + 7] = 1;		 // Tex

		vertices[i * 16 + offset + 8] = cos(i * 2 * pi<GLfloat>() / defNumOfTrianglesOnCircle);
		vertices[i * 16 + offset + 9] = -y;
		vertices[i * 16 + offset + 10] = sin(i * 2 * pi<GLfloat>() / defNumOfTrianglesOnCircle);
		vertices[i * 16 + offset + 11] = cos(i * 2 * pi<GLfloat>() / defNumOfTrianglesOnCircle);
		vertices[i * 16 + offset + 12] = 0;
		vertices[i * 16 + offset + 13] = sin(i * 2 * pi<GLfloat>() / defNumOfTrianglesOnCircle);
		vertices[i * 16 + offset + 14] = i % 2; // Tex
		vertices[i * 16 + offset + 15] = 0;		// Tex
	}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verticesArraySize, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);
}

void FrustumCone::Draw(mat4 parentModel)
{
	mat4 worldMatrix = parentModel * model;

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(worldMatrix));

	glBindVertexArray(VAO);
		glUniform1i(glGetUniformLocation(this->shader->Program, "material.diffuse"), this->sideTextureId);
		glDrawArrays(GL_TRIANGLE_FAN, 0, defNumOfTrianglesOnCircle + 2);
		glDrawArrays(GL_TRIANGLE_FAN, defNumOfTrianglesOnCircle + 2, defNumOfTrianglesOnCircle + 2);

		glUniform1i(glGetUniformLocation(this->shader->Program, "material.diffuse"), this->baseTextureId);
		glDrawArrays(GL_TRIANGLE_STRIP, (defNumOfTrianglesOnCircle + 2) * 2, (defNumOfTrianglesOnCircle + 2) * 2);
	glBindVertexArray(0);
}


void FrustumCone::GenerateCircle(GLfloat* retArray, int defNumOfTrianglesOnCircle, int offset, GLfloat y, GLfloat rCutOff)
{
	retArray[offset + 0 + 0] = 0;
	retArray[offset + 0 + 1] = y;
	retArray[offset + 0 + 2] = 0;
	retArray[offset + 0 + 3] = 0;
	retArray[offset + 0 + 4] = sign(y);
	retArray[offset + 0 + 5] = 0;
	retArray[offset + 0 + 6] = 0.5f; // Tex
	retArray[offset + 0 + 7] = 0.5f; // Tex

	for (int i = 0; i <= defNumOfTrianglesOnCircle; i++)
	{
		retArray[i * 8 + offset + 8] = cos(i * 2 * pi<GLfloat>() / defNumOfTrianglesOnCircle) * (1.0 - rCutOff);
		retArray[i * 8 + offset + 9] = y;
		retArray[i * 8 + offset + 10] = sin(i * 2 * pi<GLfloat>() / defNumOfTrianglesOnCircle) * (1.0 - rCutOff);
		retArray[i * 8 + offset + 11] = 0;
		retArray[i * 8 + offset + 12] = sign(y);
		retArray[i * 8 + offset + 13] = 0;
		retArray[i * 8 + offset + 14] = cos(i * 2 * pi<GLfloat>() / defNumOfTrianglesOnCircle) / 2 + 0.5f; // Tex
		retArray[i * 8 + offset + 15] = sin(i * 2 * pi<GLfloat>() / defNumOfTrianglesOnCircle) / 2 + 0.5f; // Tex
	}
}


bool FrustumCone::Overlap(Cylinder* cylinder)
{
	return this->boundingBox->Overlap(cylinder->boundingBox);
}