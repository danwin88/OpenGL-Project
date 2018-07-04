#include "Box.h"

Box::Box(){} 

Box::Box(Shader* shader, vec3 pos, vec3 size, vec3 rotAngleDeg, int oxTextureId, int oyTextureId, int ozTextureId, int textureRepeat)
	: Box(shader, pos, size, rotAngleDeg, oxTextureId, oyTextureId, ozTextureId, textureRepeat, pos, size, rotAngleDeg)
{	}

Box::Box(Shader* shader, vec3 pos, vec3 size, vec3 rotAngleDeg, int oxTextureId, int oyTextureId, int ozTextureId, int textureRepeat, vec3 bbPos, vec3 bbSize, vec3 bbRotAngleDeg)
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

	GLfloat boxVertices[] = {
		// Positions			// Normals				// Texture Coords
		-0.5f, -0.5f, -0.5f,	0.0f,  0.0f, -1.0f,		0.0f,  textureRepeat,					
		0.5f, -0.5f, -0.5f,		0.0f,  0.0f, -1.0f,		textureRepeat,  textureRepeat,			
		0.5f,  0.5f, -0.5f,		0.0f,  0.0f, -1.0f,		textureRepeat,  0.0f,					
		0.5f,  0.5f, -0.5f,		0.0f,  0.0f, -1.0f,		textureRepeat,  0.0f,					
		-0.5f,  0.5f, -0.5f,	0.0f,  0.0f, -1.0f,		0.0f,  0.0f,							
		-0.5f, -0.5f, -0.5f,	0.0f,  0.0f, -1.0f,		0.0f,  textureRepeat,					

		-0.5f, -0.5f,  0.5f,	0.0f,  0.0f,  1.0f,		0.0f,  textureRepeat,			
		0.5f, -0.5f,  0.5f,		0.0f,  0.0f,  1.0f,		textureRepeat,  textureRepeat,	
		0.5f,  0.5f,  0.5f,		0.0f,  0.0f,  1.0f,		textureRepeat,  0.0f,			
		0.5f,  0.5f,  0.5f,		0.0f,  0.0f,  1.0f,		textureRepeat,  0.0f,			
		-0.5f,  0.5f,  0.5f,	0.0f,  0.0f,  1.0f,		0.0f,  0.0f,					
		-0.5f, -0.5f,  0.5f,	0.0f,  0.0f,  1.0f,		0.0f,  textureRepeat,			

		-0.5f,  0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	textureRepeat,  0.0f,					
		-0.5f,  0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	0.0f,  0.0f,							
		-0.5f, -0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	0.0f,  textureRepeat,					
		-0.5f, -0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	0.0f,  textureRepeat,					
		-0.5f, -0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	textureRepeat,  textureRepeat,			
		-0.5f,  0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	textureRepeat,  0.0f,					
																								
		0.5f,  0.5f,  0.5f,		1.0f,  0.0f,  0.0f,		textureRepeat,  0.0f,					
		0.5f,  0.5f, -0.5f,		1.0f,  0.0f,  0.0f,		0.0f,  0.0f,							
		0.5f, -0.5f, -0.5f,		1.0f,  0.0f,  0.0f,		0.0f,  textureRepeat,					
		0.5f, -0.5f, -0.5f,		1.0f,  0.0f,  0.0f,		0.0f,  textureRepeat,					
		0.5f, -0.5f,  0.5f,		1.0f,  0.0f,  0.0f,		textureRepeat,  textureRepeat,			
		0.5f,  0.5f,  0.5f,		1.0f,  0.0f,  0.0f,		textureRepeat,  0.0f,					

		-0.5f, -0.5f, -0.5f,	0.0f, -1.0f,  0.0f,		0.0f,  textureRepeat,
		0.5f, -0.5f, -0.5f,		0.0f, -1.0f,  0.0f,		textureRepeat,  textureRepeat,
		0.5f, -0.5f,  0.5f,		0.0f, -1.0f,  0.0f,		textureRepeat,  0.0f,
		0.5f, -0.5f,  0.5f,		0.0f, -1.0f,  0.0f,		textureRepeat,  0.0f,
		-0.5f, -0.5f,  0.5f,	0.0f, -1.0f,  0.0f,		0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, -1.0f,  0.0f,		0.0f,  textureRepeat,

		-0.5f,  0.5f, -0.5f,	0.0f,  1.0f,  0.0f,		0.0f,  textureRepeat,
		0.5f,  0.5f, -0.5f,		0.0f,  1.0f,  0.0f,		textureRepeat,  textureRepeat,
		0.5f,  0.5f,  0.5f,		0.0f,  1.0f,  0.0f,		textureRepeat,  0.0f,
		0.5f,  0.5f,  0.5f,		0.0f,  1.0f,  0.0f,		textureRepeat,  0.0f,
		-0.5f,  0.5f,  0.5f,	0.0f,  1.0f,  0.0f,		0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,	0.0f,  1.0f,  0.0f,		0.0f,  textureRepeat
	};

	// create boxVAO 
	glGenVertexArrays(1, &boxVAO);
	// create boxVBO
	glGenBuffers(1, &boxVBO);

	// set boxVAO as current one
	glBindVertexArray(boxVAO);
	// connect VBO to VAO
	glBindBuffer(GL_ARRAY_BUFFER, boxVBO);
	// set buffer data params - its size, pointer do vertices, way of drawing ( static, dynamic ... )
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 288, boxVertices, GL_STATIC_DRAW);
	// glVertexAttribPointer - tell OpenGL how it should interpret the vertex data (per vertex attribute) 
	// The first parameter specifies which vertex attribute we want to configure.Remember that we specified the location of the position vertex attribute in the vertex shader with layout(location = 0).This sets the location of the vertex attribute to 0 and since we want to pass data to this vertex attribute, we pass in 0.
	// The next argument specifies the size of the vertex attribute.The vertex attribute is a vec3 so it is composed of 3 values.
	// The third argument specifies the type of the data which is GL_FLOAT(a vec* in GLSL consists of floating point values).
	// The next argument specifies if we want the data to be normalized.If we set this to GL_TRUE all the data that has a value not between 0 (or -1 for signed data) and 1 will be mapped to those values.We leave this at GL_FALSE.
	// The fifth argument is known as the stride and tells us the space between consecutive vertex attribute sets.Since the next set of position data is located exactly 3 times the size of a GLfloat away we specify that value as the stride.Note that since we know that the array is tightly packed(there is no space between the next vertex attribute value) we could've also specified the stride as 0 to let OpenGL determine the stride (this only works when values are tightly packed). Whenever we have more vertex attributes we have to carefully define the spacing between each vertex attribute but we'll get to see more examples of that later on.
	// The last parameter is of type GLvoid* and thus requires that weird cast.This is the offset of where the position data begins in the buffer.Since the position data is at the start of the data array this value is just 0. We will explore this parameter in more detail later on
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// unset vertex array = set current one to 0
	glBindVertexArray(0);
}

Box::~Box()
{
	glDeleteBuffers(1, &boxVBO);
	glDeleteBuffers(1, &boxVAO);
}


void Box::UpdateModel()
{
	model = mat4();
	model = translate(model, this->pos);
	model = rotate(model, radians(this->rotAngleDeg.x), vec3(1, 0, 0));
	model = rotate(model, radians(this->rotAngleDeg.y), vec3(0, 1, 0));
	model = rotate(model, radians(this->rotAngleDeg.z), vec3(0, 0, 1));
	model = scale(model, this->size);

	this->boundingBox->UpdateBoundingBox(this->pos, this->size, this->rotAngleDeg);
}

void Box::Move(vec3 pos)
{
	this->pos += pos;
	UpdateModel();
}
void Box::Resize(vec3 size)
{
	this->size += size;
	UpdateModel();
}
void Box::Rotate(vec3 rotAngleDeg)
{
	this->rotAngleDeg += rotAngleDeg;
	UpdateModel();
}

void Box::Draw(mat4 parentModel)
{
	// convert local coordinates to the world coordinates
	mat4 worldMatrix = parentModel * model;
	// set boxVAO as current one
	glBindVertexArray(boxVAO);
	// set the shader modelLoc variable to worldMatrix
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(worldMatrix));
	// set the shader material.diffuse variable ( texture ) to oxTextureId texture index. It will be used to cover ox side of the box
	glUniform1i(glGetUniformLocation(this->shader->Program, "material.diffuse"), this->oxTextureId);
	glDrawArrays(GL_TRIANGLES, 0, 12);
	// set the shader material.diffuse variable ( texture ) to ozTextureId texture index. It will be used to cover oz side of the box
	glUniform1i(glGetUniformLocation(this->shader->Program, "material.diffuse"), this->oyTextureId);
	glDrawArrays(GL_TRIANGLES, 12, 12);
	// set the shader material.diffuse variable ( texture ) to oyTextureId texture index. It will be used to cover oy side of the box
	glUniform1i(glGetUniformLocation(this->shader->Program, "material.diffuse"), this->ozTextureId);
	glDrawArrays(GL_TRIANGLES, 24, 12);
	// unset VAO - set to 0
	glBindVertexArray(0);
}


bool Box::Overlap(Box* box)
{
	return this->boundingBox->Overlap(box->boundingBox);
}

