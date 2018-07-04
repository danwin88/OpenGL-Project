


#include "OpenGL.h"

#include "Singleton.h"

#include "Shader.h"

using namespace glm;

class CameraManager
{
public:
	enum Camera_Movement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};


	// Camera Attributes
	vec3 Position;
	vec3 Front; // poits the direction camera looks to
	vec3 Up; // points the "up" direction
	vec3 Right;
	vec3 WorldUp;
	// Eular Angles
	GLfloat Yaw;
	GLfloat Pitch;
	// Camera options
	GLfloat MovementSpeed;
	GLfloat MouseSensitivity;
	GLfloat Zoom;


	// Default camera values
	const GLfloat SPEED = 3.0f;
	const GLfloat SENSITIVTY = 0.25f;
	const GLfloat ZOOM = 45.0f;


	CameraManager* Init(vec3 position = vec3(0.0f, 0.0f, 0.0f), vec3 up = vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = -90, GLfloat pitch = 0.0);
	CameraManager* Init(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch);

	// Returns the view matrix calculated using Eular Angles and the LookAt Matrix
	mat4 GetViewMatrix();
	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true);
	// Moves/alters the camera positions based on user input
	void ProcessKeyboard(bool *keys, GLfloat deltaTime);
	// set camera variables in shader
	void SetCameraPositionAndTransformationInShader(Shader *shader, GLfloat aspectRatio);
	// used when restarting scene to set up camera to initial state
	void Restart();

private:
	// Calculates the front vector from the Camera's (updated) Eular Angles
	void UpdateCameraVectors();

};

// used to make CameraManager singleton
typedef Singleton<CameraManager> TheCameraManager;