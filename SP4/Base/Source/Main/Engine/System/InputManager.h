/****************************************************************************/
/*!
\file InputManager.h
\author Ryan Lim Rui An
\par email: 150577L@mymail.nyp.edu.sg
\brief
Defines the Input Manager that handles all forms of input
*/
/****************************************************************************/


#ifndef _INPUTMANAGER_H
#define _INPUTMANAGER_H

#include "Vector3.h"
#include "../../Base/Source/Main/Engine/Internal/SingletonTemplate.h"
#include "State.h"
#include <map>

class InputManager : public SingletonTemplate<InputManager>
{
public:

	InputManager();
	void HandleUserInput();
	bool GetKeyValue(char);
	Vector3 GetMousePosition();
	void SetMousePosition(Vector3);
	void SetMouseToScreenCenter();
	void UpdateMouse();

	void Update();

	void SetScreenSize(float, float);

	float cIM_ScreenWidth, cIM_ScreenHeight;
	float cIM_CameraYaw = 0, cIM_CameraPitch = 0;
	bool cIM_inMouseMode = false;

	STATE GetMouseState(MOUSE);

	void KeyboardInput();
	char GetKeyPressed();
	void KeyPressedUpdate();
	STATE CheckKeyPressed(char);

private:
	std::map<MOUSE, STATE> Mouse;
	std::map<char, STATE> KeyInput;
	Vector3 MousePosition;
	bool cIM_Keys[256];
};

#endif