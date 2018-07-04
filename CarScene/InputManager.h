

#pragma once

#include "OpenGL.h"

#include "Singleton.h"

class InputManager
{
public:
	// the callback method used by GLFW library to process key events 
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	// the callback method used by GLFW library to process mouse events
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);

	void Restart();

	// bufor for keyboard keys
	bool keys[1024]; 

	// the amount of pixels mous moved
	GLfloat xoffset;
	GLfloat yoffset;

	// this flag indicates that since last main loop pass there was mouse event
	// without it the xoffset and yoffset will be cumulated on each main loop pass even if there was only one mouse event
	bool HasData = false;
	// flag indicates that ( according to e.g. some key event ) HUD should be shown
	bool ShowHud = false;

private:
	// duplicated from ScreenManager - used to calculate initial mouse position
	const GLuint WIDTH = 800, HEIGHT = 600;
	// used to calculate initial mouse position
	GLfloat lastX = WIDTH / 2.0;
	GLfloat lastY = HEIGHT / 2.0;
	bool firstMouse = true;
};

typedef Singleton<InputManager> TheInputManager;