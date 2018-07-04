

#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "OpenGL.h"

#include "Shader.h"
#include "FileManager.h"

#include "Singleton.h"

using namespace glm;

class ScreenManager
{
public:
	// width and height of the window
	const GLuint WIDTH = 800, HEIGHT = 600;
	//aspect ration of main window
	const GLfloat ASPECT_RATIO = (GLfloat)WIDTH / (GLfloat)HEIGHT;
	// buffers to FPS, GameTime, TotalGameTime texts
	char FPS[10];
	char GameTime[10];
	int GameTimeInt;
	char TotalGameTime[10];

	// flag used to determine events which should be done only once per second ( e.g. drawing FPS, game time )
	// without this this text will be change to fast ( on every main loop pass ) and blinking
	bool DoOncePerSecondFlag;
	// flag indicating restarting of the scene
	bool RestartFlag = false;

	// set screen with initial values when the ScreenManager is first used
	GLFWwindow* Init();
	// clear scene on the begining of each main  loop pass
	void ClearScene(vec4 clearColor);
	// metods calculating and fetching delta time
	GLfloat CalculateDeltaTime();
	GLfloat GetDeltaTime();

	void Restart();
private:
	// Deltatime
	double deltaTime = 0.0f;	// Time between current frame and last frame
	double lastFrame = 0.0f;  	// Time of last frame

	// used to indicate that it is first iteration of the main loop
	bool firstIteration;

	// used to enable or disable vertical synchronization. If enabled could limit FPS to 60
	void SetVerticalSync(bool bVerticalSync);
};

typedef Singleton<ScreenManager> TheScreenManager;

