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
#include <map>

class InputManager : public SingletonTemplate<InputManager>
{
public:
	enum Type
	{
		CLICK,
		HOLD,
		RELEASE,
		UNTOUCHED,
		MOUSETYPE_NUM
	};
	enum MouseClick
	{
		MOUSE_L,
		MOUSE_R,
		MOUSE_NUM,
	};

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

	Type GetMouseState(MouseClick);

	void KeyboardInput();
	char GetKeyPressed();
	void KeyPressedUpdate();
	Type CheckKeyPressed(char);

private:
	std::map<MouseClick, Type> Mouse;
	std::map<char, Type> KeyInput;
	Vector3 MousePosition;
	bool cIM_Keys[256];
};

#endif