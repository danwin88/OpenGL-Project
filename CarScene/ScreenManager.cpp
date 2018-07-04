#include "ScreenManager.h"


GLFWwindow* ScreenManager::Init()
{
	// Init GLFW
	int success = glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Car scene", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// GLFW Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	// Define the viewport dimensions
	glViewport(0, 0, WIDTH, HEIGHT);

	// OpenGL options
	glEnable(GL_DEPTH_TEST);

	// SetVerticalSync(false);  // disable GLFW sync to VSync of monitor => not limit to 60FPS

	firstIteration = true;

	return window;
}

// Clear the colorbuffer and depth buffer
void ScreenManager::ClearScene(vec4 clearColor) {
	glClearColor(clearColor.x, clearColor.y, clearColor.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// Calculate deltatime of current frame
GLfloat ScreenManager::CalculateDeltaTime() {
	double currentFrame = glfwGetTime();
	this->deltaTime = currentFrame - this->lastFrame;
	this->lastFrame = currentFrame;

	itoa(TheFileManager::Instance()->TotalGamgeTimeInt + TheScreenManager::Instance()->GameTimeInt, this->TotalGameTime, 10);

	double fps = 1 / deltaTime;
	int iFps = fps;

	if ((1.0 - (currentFrame - ((int)currentFrame)) < this->deltaTime) || firstIteration)
	{
		DoOncePerSecondFlag = true;

		itoa(iFps, this->FPS, 10);
		itoa(currentFrame, this->GameTime, 10);
		GameTimeInt = (int)currentFrame;
	}
	else
	{
		DoOncePerSecondFlag = false;
	}

	firstIteration = false;

	return this->deltaTime;
}
GLfloat ScreenManager::GetDeltaTime() {
	return this->deltaTime;
}


void ScreenManager::SetVerticalSync(bool bVerticalSync) {
	if (bVerticalSync) {
		glfwSwapInterval(1);
	}
	else {
		glfwSwapInterval(0);
	}
}

void ScreenManager::Restart()
{

}
