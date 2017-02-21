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
	enum MouseType
	{
		MOUSE_CLICK,
		MOUSE_HOLD,
		MOUSE_RELEASE,
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

	void SetScreenSize(float, float);
	MouseType GetMouseState(MouseClick);

	float cIM_ScreenWidth, cIM_ScreenHeight;
	float cIM_CameraYaw = 0, cIM_CameraPitch = 0;
	bool cIM_inMouseMode = false;

private:
	//MouseClick* MouseClick;
	//MouseType* MouseType;
	std::map<MouseClick, MouseType> Mouse;
	Vector3 MousePosition;
	bool cIM_Keys[256];
};

#endif