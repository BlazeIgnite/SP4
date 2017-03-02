#include "Application.h"

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>

#include "../../Engine/System/SceneSystem.h"
#include "../../Engine/System/RenderSystem.h"
#include "../../Engine/System/LuaSystem.h"

#include "../Scene/SceneLevelSelection.h"
#include "../Scene/Scene_Assignment1.h"
#include "../Scene/SceneLevel1.h"
#include "../Scene/MainMenu.h"
#include "../Scene/SceneBattles.h"
#include "../Scene/Town.h"
#include "../Scene/SceneWin.h"
#include "../Scene/SceneLose.h"
#include "../Scene/SceneCharacterSelection.h"
#include "../Scene/SceneTutorial.h"
#include "../Scene/SceneLevel3.h"
#include "../Scene/SceneLevel4.h"
#include "../Audio/Audio_Player.h"

GLFWwindow* m_window;
const unsigned char FPS = 150; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame
int Application::ScreenHeight = 0;
int Application::ScreenWidth = 0;

//Define an error callback
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

//Define the key input callback
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}


void resize_callback(GLFWwindow* window, int w, int h)
{
	Application::SetWindowWidth(w);
	Application::SetWindowHeight(h);
	glViewport(0, 0, w, h);
}

bool Application::IsKeyPressed(unsigned short key)
{
    return ((GetAsyncKeyState(key) & 0x8001) != 0);
}
bool Application::IsMousePressed(unsigned short key) //0 - Left, 1 - Right, 2 - Middle
{
	return glfwGetMouseButton(m_window, key) != 0;
}
void Application::GetCursorPos(double *xpos, double *ypos)
{
	glfwGetCursorPos(m_window, xpos, ypos);
}
int Application::GetWindowWidth()
{
	return ScreenWidth;
}
int Application::GetWindowHeight()
{
	return ScreenHeight;
}
void Application::SetWindowWidth(const int& w)
{
	ScreenWidth = w;
}
void Application::SetWindowHeight(const int& h)
{
	ScreenHeight = h;
}

void Application::ChangeWindowSize(const int& w, const int& h)
{
	SetWindowWidth(w);
	SetWindowHeight(h);
	glfwSetWindowSize(m_window, ScreenWidth, ScreenHeight);
}

void Application::FullScreenWindowSize()
{
	SetWindowWidth(glfwGetVideoMode(glfwGetPrimaryMonitor())->width);
	SetWindowHeight(glfwGetVideoMode(glfwGetPrimaryMonitor())->height);
	glfwSetWindowSize(m_window, ScreenWidth, ScreenHeight);
}

Application::Application()
{
}

Application::~Application()
{
}

void Application::Init()
{
	//Set the error callback
	glfwSetErrorCallback(error_callback);

	// Init the Scene System
	SceneSystem::Instance().Init();
	Player::Instance().LoadPlayer(0);
	Quit = false;
	//Initialize GLFW
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	//Set the GLFW window creation hints - these are optional
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 
	//Borderless
	//glfwWindowHint(GLFW_DECORATED, GL_FALSE);

	// SIDE NOTE: DO NOT BUG TEST IN FULL SCREEN. IF IT LAGS OUT, YOU CANNOT CLOSE THE WINDOW!
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	//Obtain Width and Height values from the monitor;

	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

	//Create a window and create its OpenGL context
	//ScreenWidth = 800;
	//ScreenHeight = 600;
	ScreenWidth = mode->width;
	ScreenHeight = mode->height;
	m_window = glfwCreateWindow(ScreenWidth, ScreenHeight, "Framework", NULL, NULL);

	//If the window couldn't be created
	if (!m_window)
	{
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//This function makes the context of the specified window current on the calling thread. 
	glfwMakeContextCurrent(m_window);

	//Sets the key callback
	//glfwSetKeyCallback(m_window, key_callback);
	glfwSetWindowSizeCallback(m_window, resize_callback);

	glewExperimental = true; // Needed for core profile
	//Initialize GLEW
	GLenum err = glewInit();

	//If GLEW hasn't initialized
	if (err != GLEW_OK) 
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		//return -1;
	}

	AudioPlayer::Instance().Init();

	// Assign Scene Renderer
	RenderSystem* Renderer = new RenderSystem();
	Renderer->Init();
	SceneSystem::Instance().SetRenderSystem(*Renderer);

	MainMenu* temp3 = new MainMenu();
	temp3->Init();
	SceneSystem::Instance().AddScene(*temp3);
	
	Town* temp4 = new Town();
	temp4->SetEntityID("Town_Scene");
	SceneSystem::Instance().AddScene(*temp4);

	SceneLose* temp2 = new SceneLose();
	temp2->SetEntityID("Lose_Scene");
	SceneSystem::Instance().AddScene(*temp2);

	SceneBattles* temp = new SceneBattles();
	temp->SetEntityID("Battle_Scene");
	SceneSystem::Instance().AddScene(*temp);

	SceneLevelSelection* temp5 = new SceneLevelSelection();
	temp5->SetEntityID("LevelSelection_Scene");
	SceneSystem::Instance().AddScene(*temp5);
	
	SceneCharacterSelection* temp6 = new SceneCharacterSelection();
	temp6->SetEntityID("CharacterSelection_Scene");
	SceneSystem::Instance().AddScene(*temp6);

	SceneTutorial* temp7 = new SceneTutorial();
	temp7->SetEntityID("Tutorial_Scene");
	SceneSystem::Instance().AddScene(*temp7);

	SceneLevel1* temp9 = new SceneLevel1();
	temp9->SetEntityID("Level1_Scene");
	SceneSystem::Instance().AddScene(*temp9);

	SceneWin* temp8 = new SceneWin();
	temp8->SetEntityID("Win_Scene");
	SceneSystem::Instance().AddScene(*temp8);

	SceneLevel3* temp10 = new SceneLevel3();
	temp10->SetEntityID("Level3_Scene");
	SceneSystem::Instance().AddScene(*temp10);

	SceneLevel4* temp11 = new SceneLevel4();
	temp11->SetEntityID("Level4_Scene");
	SceneSystem::Instance().AddScene(*temp11);

}

void Application::Run()
{
	HWND hwnd = GetActiveWindow();

	m_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
	while (!glfwWindowShouldClose(m_window) && !IsKeyPressed(VK_ESCAPE) && !Quit)
	{
		m_dElaspedTime = m_timer.getElapsedTime();
		if (hwnd == GetActiveWindow())
		{
			Update();
			SceneSystem::Instance().GetCurrentScene().Render();
		}
		//Swap buffers
		glfwSwapBuffers(m_window);
		//Get and organize events, like keyboard and mouse input, window resizing, etc...
		glfwPollEvents();
        m_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.   
	} 
}

void Application::Update()
{
	// Update threads
	m_dAccumulatedTime_ThreadOne += m_dElaspedTime;
	if (m_dAccumulatedTime_ThreadOne > 1 / frameTime)
	{
		SceneSystem::Instance().cSS_InputManager->UpdateMouse();
		SceneSystem::Instance().cSS_InputManager->HandleUserInput();
		//SceneSystem::Instance().cSS_PlayerUIManager->Update((float)m_dElaspedTime);
		SceneSystem::Instance().GetCurrentScene().Update((float)m_dElaspedTime);
		InputManager::Instance().Update();
		
		m_dAccumulatedTime_ThreadOne = 0.0;
	}
	m_dAccumulatedTime_ThreadTwo += m_dElaspedTime;
	if (m_dAccumulatedTime_ThreadTwo > 1 / frameTime * 5)
	{
		//SceneSystem::Instance().cSS_PlayerUIManager->UpdateStats((float)m_dElaspedTime);
		//MusicSystem::Instance().Update((float)m_dElaspedTime);
		m_dAccumulatedTime_ThreadTwo = 0.0;
	}
}

void Application::Exit()
{
	//Check if the ESC key had been pressed or if the window had been closed
	LuaSystem::Instance().GameSave();
	SceneSystem::Instance().ClearMemoryUsage();
	AudioPlayer::Instance().Exit();
	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(m_window);
	//Finalize and clean up GLFW
	glfwTerminate();
}

void Application::QuitGame()
{
	Quit = true;
}