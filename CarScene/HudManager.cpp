#include "HudManager.h"

void HudManager::Init(Shader *fontShader, Shader *backgroundShader, GLFWwindow* window)
{
	this->fontShader = fontShader;
	this->backgroundShader = backgroundShader;
	this->window = window;


	GLfloat boxVertices[] = {
		// Positions				// Color		// Texture Coords
		-0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 0.0f,	1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,		1.0f, 0.0f, 0.0f,	1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,		1.0f, 0.0f, 0.0f,	1.0f,  1.0f,
		-0.5f,  0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	0.0f,  1.0f,
		-0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	0.0f,  0.0f,
	};


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 288, boxVertices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat))); 	// Tex
	glEnableVertexAttribArray(2); 																			// Tex

	glBindVertexArray(0);
}

void HudManager::Draw()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	backgroundShader->Use();
	glUniform4f(glGetUniformLocation(backgroundShader->Program, "hudColor"), 0.25f, 0.25f, 0.25f, 0.75f);

	glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

	glDisable(GL_BLEND);


	TheTextManager::Instance()->PrepareBeforeRenderText(fontShader);

	TheTextManager::Instance()->RenderText(*fontShader, "(N) New",				320.0f, 330.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.6f));
	TheTextManager::Instance()->RenderText(*fontShader, "(S) Save to file",		320.0f, 300.0f, 0.5f, glm::vec3(0.4, 0.7f, 0.7f));
	TheTextManager::Instance()->RenderText(*fontShader, "(E) Exit",				320.0f, 270.0f, 0.5f, glm::vec3(0.5, 0.7f, 0.8f));
	TheTextManager::Instance()->RenderText(*fontShader, "(Esc) Back",			320.0f, 240.0f, 0.5f, glm::vec3(0.6, 0.7f, 0.9f));

	TheTextManager::Instance()->CleanAfterRenderText();
}

void HudManager::ProcessInputKeys(bool *keys)
{
	if (keys[GLFW_KEY_N])
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
		TheScreenManager::Instance()->RestartFlag = true;
	}
	if (keys[GLFW_KEY_S])
	{
		TheFileManager::Instance()->WriteCurrentPlayTime(TheScreenManager::Instance()->GameTime, TheScreenManager::Instance()->TotalGameTime);
		TheInputManager::Instance()->ShowHud = false;
	}
	if (keys[GLFW_KEY_E])
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
		TheScreenManager::Instance()->RestartFlag = false;
	}
}

void HudManager::Restart()
{
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &VAO);
}