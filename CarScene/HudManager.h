
#pragma once

#include <iostream>
#include "Singleton.h"

#include "OpenGL.h"

#include "Shader.h"
#include "ScreenManager.h"
#include "TextManager.h"
#include "LightManager.h"
#include "InputManager.h"
#include "FileManager.h"

// this class responsibility is to display HUD ( semi transparent menu with few options )
class HudManager
{
private:
	// two shaders are usesd one to write text and one to display background ( colored rectangle )
	Shader *fontShader, *backgroundShader;
	// reference to mainwindow - to process close event
	GLFWwindow* window;
	GLuint VBO, VAO;

public:
	// set properties before instance of manager is first used
	void Init(Shader *fontShader, Shader *backgroundShader, GLFWwindow* window);
	void Draw();
	// HudManager has its own method to proces keys - thanks to it there will be no conflict with keys using during ordinary scene presentation
	void ProcessInputKeys(bool *keys);
	void Restart();
};

typedef Singleton<HudManager> TheHudManager;