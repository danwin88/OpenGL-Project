#include "CameraManager.h"



	// Constructor with vectors
	CameraManager* CameraManager::Init(vec3 position, vec3 up, GLfloat yaw , GLfloat pitch)
	{
		this->Front = vec3(0.0f, 0.0f, -1.0f);
		this->MovementSpeed = SPEED;
		this->MouseSensitivity = SENSITIVTY;
		this->Zoom = ZOOM;

		this->Position = position;
		this->WorldUp = up;
		this->Yaw = yaw;
		this->Pitch = pitch;
		this->UpdateCameraVectors();

		return this;
	}
	// Constructor with scalar values
	CameraManager*  CameraManager::Init(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch)
	{
		this->Front = vec3(0.0f, 0.0f, -1.0f);
		this->MovementSpeed = SPEED;
		this->MouseSensitivity = SENSITIVTY;
		this->Zoom = ZOOM;

		this->Position = vec3(posX, posY, posZ);
		this->WorldUp = vec3(upX, upY, upZ);
		this->Yaw = yaw;
		this->Pitch = pitch;
		this->UpdateCameraVectors();

		return this;
	}


	mat4 CameraManager::GetViewMatrix()
	{
		return lookAt(this->Position, this->Position + this->Front, this->Up);
	}


	void CameraManager::ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch)
	{
		xoffset *= this->MouseSensitivity;
		yoffset *= this->MouseSensitivity;

		this->Yaw += xoffset;
		this->Pitch += yoffset;

		// Make sure that when pitch is out of bounds, screen doesn't get flipped
		if (constrainPitch)
		{
			if (this->Pitch > 89.0f)
				this->Pitch = 89.0f;
			if (this->Pitch < -89.0f)
				this->Pitch = -89.0f;
		}

		// Update Front, Right and Up Vectors using the updated Eular angles
		this->UpdateCameraVectors();
	}

	void CameraManager::ProcessKeyboard(bool *keys, GLfloat deltaTime)
	{
		// Camera controls
		if (keys[GLFW_KEY_LEFT_SHIFT])
		{
			GLfloat velocity = this->MovementSpeed * deltaTime;
			if (keys[GLFW_KEY_LEFT_CONTROL])
				velocity *= 2;

			if (keys[GLFW_KEY_W])
				this->Position += this->Front * velocity;
			if (keys[GLFW_KEY_S])
				this->Position -= this->Front * velocity;
			if (keys[GLFW_KEY_A])
				this->Position -= this->Right * velocity;
			if (keys[GLFW_KEY_D])
				this->Position += this->Right * velocity;
		}
	}

	void CameraManager::UpdateCameraVectors()
	{
		// Calculate the new Front vector
		vec3 front;
		front.x = cos(radians(this->Yaw)) * cos(radians(this->Pitch));
		front.y = sin(radians(this->Pitch));
		front.z = sin(radians(this->Yaw)) * cos(radians(this->Pitch));
		this->Front = normalize(front);
		// Also re-calculate the Right and Up vector
		this->Right = normalize(cross(this->Front, this->WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		this->Up = normalize(cross(this->Right, this->Front));
	}

	void CameraManager::SetCameraPositionAndTransformationInShader(Shader *shader, GLfloat aspectRatio)
	{
		GLint viewPosLoc = glGetUniformLocation(shader->Program, "viewPos");
		glUniform3f(viewPosLoc, Position.x, Position.y, Position.z);
		// Create camera transformations
		mat4 view;
		view = GetViewMatrix();
		mat4 projection = perspective(Zoom, aspectRatio, 0.1f, 100.0f);
		// Get the uniform locations
		GLint viewLoc = glGetUniformLocation(shader->Program, "view");
		GLint projLoc = glGetUniformLocation(shader->Program, "projection");
		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(projection));
	}

	void CameraManager::Restart()
	{

	}