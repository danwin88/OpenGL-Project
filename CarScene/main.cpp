
#include "main.h"

#include "FileManager.h"


#pragma comment( lib, "lib/OPENGL32.lib" )	
#pragma comment( lib, "lib/glew32s.lib" )	
#pragma comment( lib, "lib/glfw3.lib" )	
#pragma comment( lib, "lib/soil.lib" )	

#pragma comment( lib, "freetype.lib" )	

using namespace glm;


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

// The MAIN function, from here we start the application and run the game loop
int main()
{
	do {
		GLFWwindow* window = TheScreenManager::Instance()->Init();

 		CameraManager *camera = TheCameraManager::Instance()->Init(vec3(0.0f, 1.0f, 3.0f));

		glfwSetKeyCallback(window, key_callback);
		glfwSetCursorPosCallback(window, mouse_callback);


		// Build and compile our shaders program
		Shader lightingShader("./Shaders/lighting.vs", "./Shaders/lighting.frag");
		Shader fontShader("./Shaders/font.vs", "./Shaders/font.frag");
		Shader hudBackground("./Shaders/hudBackground.vs", "./Shaders/hudBackground.frag");

		// load textures
		int texCarBody = TheTextureManager::Instance()->LoadFromFile("./Textures/carBody.png", "carBody");
		int texCarBodyTop = TheTextureManager::Instance()->LoadFromFile("./Textures/carBodyTop.png", "carBodyTop");
		int texCarBodySide = TheTextureManager::Instance()->LoadFromFile("./Textures/carBodySide.png", "carBodySide");
		int texTyreSide = TheTextureManager::Instance()->LoadFromFile("./Textures/tyreSide.png", "tyreSide");
		int texTyreFront = TheTextureManager::Instance()->LoadFromFile("./Textures/tyreFront.png", "tyreFront");
		int texCarBody2 = TheTextureManager::Instance()->LoadFromFile("./Textures/carBody2.png", "carBody2");

		int texBrick1 = TheTextureManager::Instance()->LoadFromFile("./Textures/brick1.png", "brick1");
		int texHedge1 = TheTextureManager::Instance()->LoadFromFile("./Textures/hedge1.png", "hedge1");
		int texHedge2 = TheTextureManager::Instance()->LoadFromFile("./Textures/hedge2.png", "hedge2");
		int texRoofTiles = TheTextureManager::Instance()->LoadFromFile("./Textures/RoofTiles.png", "roofTiles");

		int texAsphalt = TheTextureManager::Instance()->LoadFromFile("./Textures/Asphalt.png", "asphalt");
		int texPavementBrick = TheTextureManager::Instance()->LoadFromFile("./Textures/pavementBrick.png", "pavementBrick");
		int texHouse1 = TheTextureManager::Instance()->LoadFromFile("./Textures/house1.png", "house1");
		int texHouse2 = TheTextureManager::Instance()->LoadFromFile("./Textures/house2.png", "house2");
		int texGrass1 = TheTextureManager::Instance()->LoadFromFile("./Textures/grass1.png", "grass1");

		int texLamp1 = TheTextureManager::Instance()->LoadFromFile("./Textures/lamp1.png", "lamp1");
		int texLamp2 = TheTextureManager::Instance()->LoadFromFile("./Textures/lamp2.png", "lamp2");
		int texMetal1 = TheTextureManager::Instance()->LoadFromFile("./Textures/metal1.png", "metal1");
		int texMetal2 = TheTextureManager::Instance()->LoadFromFile("./Textures/metal2.png", "metal2");

		// create scene
		Scene scene(&lightingShader);

		// setup initial light values
		vec3 specularLightPosiions[2];
		specularLightPosiions[0] = scene.car->posForLeftSpecularLight;
		specularLightPosiions[1] = scene.car->posForRightSpecularLight;
		vec3 specularLightDirections[2];
		specularLightDirections[0] = scene.car->dirForLeftSpecularLight;
		specularLightDirections[1] = scene.car->dirForRightSpecularLight;
		TheLightManager::Instance()->InitLightValues(4, 2, specularLightPosiions, specularLightDirections);

		// init managers ( text, hud, file )
		TheTextManager::Instance()->Init();
		TheHudManager::Instance()->Init(&fontShader, &hudBackground, window);
		TheFileManager::Instance()->Init();

		// Main Game loop
		while (!glfwWindowShouldClose(window))
		{
			// ordinary scene draw - without HUD
			if (!TheInputManager::Instance()->ShowHud)
			{
				// Calculate deltatime of current frame
				GLfloat deltaTime = TheScreenManager::Instance()->CalculateDeltaTime();

				TheCameraManager::Instance()->ProcessKeyboard(TheInputManager::Instance()->keys, deltaTime);

				if (TheInputManager::Instance()->HasData) {
					camera->ProcessMouseMovement(TheInputManager::Instance()->xoffset, TheInputManager::Instance()->yoffset);
					TheInputManager::Instance()->HasData = false;
				}

				// Clear the color buffer
				TheScreenManager::Instance()->ClearScene(TheLightManager::Instance()->ClearColor);

				// Use cooresponding shader when setting uniforms/drawing objects
				lightingShader.Use();

				TheCameraManager::Instance()->SetCameraPositionAndTransformationInShader(&lightingShader, TheScreenManager::Instance()->ASPECT_RATIO);

				// calculate light change ( in fact only specular light could change )
				vec3 specularLightPosiions[2];
				specularLightPosiions[0] = scene.car->posForLeftSpecularLight;
				specularLightPosiions[1] = scene.car->posForRightSpecularLight;
				vec3 specularLightDirections[2];
				specularLightDirections[0] = scene.car->dirForLeftSpecularLight;
				specularLightDirections[1] = scene.car->dirForRightSpecularLight;
				TheLightManager::Instance()->UpdateSpotLight(2, specularLightPosiions, specularLightDirections);


				TheLightManager::Instance()->SetLightParamsInShader(&lightingShader);

				// process any key event in scene
				scene.Update(TheInputManager::Instance()->keys, deltaTime);

				// draw every element on scene
				scene.Draw();

				// after scene has been drawn the text in left top corner are drawn ( after main scene to has it as background in transparent parts of the letters )
				TheTextManager::Instance()->PrepareBeforeRenderText(&fontShader);

				string fpsText = "fps:               " + string(TheScreenManager::Instance()->FPS);
				string gameTimeText = "game time:  " + string(TheScreenManager::Instance()->GameTime);
				string totalGameTimeText = "total time:    " + string(TheScreenManager::Instance()->TotalGameTime);
				TheTextManager::Instance()->RenderText(fontShader, fpsText, 10.0f, 570.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));
				TheTextManager::Instance()->RenderText(fontShader, gameTimeText, 10.0f, 540.0f, 0.5f, glm::vec3(0.4, 0.7f, 0.8f));
				TheTextManager::Instance()->RenderText(fontShader, totalGameTimeText, 10.0f, 510.0f, 0.5f, glm::vec3(0.5, 0.7f, 0.7f));

				TheTextManager::Instance()->CleanAfterRenderText();
				// --------------
			}
			// the HUD is drawn
			else
			{
				// draw freezed scene
				TheScreenManager::Instance()->ClearScene(TheLightManager::Instance()->ClearColor);
				lightingShader.Use();
				TheCameraManager::Instance()->SetCameraPositionAndTransformationInShader(&lightingShader, TheScreenManager::Instance()->ASPECT_RATIO);
				TheLightManager::Instance()->SetLightParamsInShader(&lightingShader);
				scene.Draw();

				// draw HUD
				TheHudManager::Instance()->Draw();
				TheHudManager::Instance()->ProcessInputKeys(TheInputManager::Instance()->keys);
			}


			// Swap the screen buffers
			glfwSwapBuffers(window);

			// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
			glfwPollEvents();
		}


		scene.~Scene();

		// Terminate GLFW, clearing any resources allocated by GLFW.
		glfwTerminate();

		TheInputManager::Instance()->Restart();
		TheScreenManager::Instance()->Restart();
		TheCameraManager::Instance()->Restart();
		TheTextureManager::Instance()->Restart();
		TheLightManager::Instance()->Restart();
		TheTextManager::Instance()->Restart();
		TheHudManager::Instance()->Restart();

	} while (TheScreenManager::Instance()->RestartFlag);

	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	TheInputManager::Instance()->key_callback(window, key, scancode, action, mode);
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	TheInputManager::Instance()->mouse_callback(window, xpos, ypos);
}
