#include "InputManager.h"


// Is called whenever a key is pressed/released via GLFW
void InputManager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		ShowHud = !ShowHud;
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

// Is called whenever a mouse event occurs via GLFW
void InputManager::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	xoffset = xpos - lastX;
	yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	HasData = true;
}

void InputManager::Restart()
{
	for(int i=0; i<1024; i++)
	{
		keys[i] = false;
	}

	HasData = false;
	ShowHud = false;

	lastX = WIDTH / 2.0;
	lastY = HEIGHT / 2.0;
	firstMouse = true;
}