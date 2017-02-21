#include "InputManager.h"
#include "../../Game/Mains/Application.h"
#include "SceneSystem.h"
#include "SimpleCommand.h"
#include "../../Base/Source/Main/Game/Systems/ObjectManager.h"

InputManager::InputManager()
{
	for (int num = 0; num < 256; ++num)
	{
		cIM_Keys[num] = false;
	}
	Mouse = std::map<MouseClick, MouseType>();
}

void InputManager::HandleUserInput()
{
    // hardcoded inputs. A need for change. So i really need everyone's help
    for (unsigned num = 0; num < SimpleCommand::TOTAL_COMMANDS; ++num)
    {
        if (Application::IsKeyPressed(SimpleCommand::m_allTheKeys[num]) && cIM_Keys[SimpleCommand::m_allTheKeys[num]] == false)
        {
            cIM_Keys[SimpleCommand::m_allTheKeys[num]] = true;
        }
        else if (!Application::IsKeyPressed(SimpleCommand::m_allTheKeys[num]) && cIM_Keys[SimpleCommand::m_allTheKeys[num]] == true)
        {
            cIM_Keys[SimpleCommand::m_allTheKeys[num]] = false;
        }
    }
}

bool InputManager::GetKeyValue(char c)
{
	return cIM_Keys[c];
}

Vector3 InputManager::GetMousePosition()
{
	return MousePosition;
}

void InputManager::SetMousePosition(Vector3 v3)
{
	MousePosition = v3;
}

void InputManager::SetScreenSize(float x, float y)
{
	cIM_ScreenWidth = x;
	cIM_ScreenHeight = y;
}

InputManager::MouseType InputManager::GetMouseState(MouseClick Click)
{
	std::map<MouseClick, MouseType>::iterator it = Mouse.find(Click);
	if (it == Mouse.end())
	{
		Mouse.insert(std::pair<MouseClick, MouseType>(Click, MOUSE_RELEASE));
		return GetMouseState(Click);
	}
	return it->second;
}

void InputManager::UpdateMouse()
{
	double x, y;
	Application::GetCursorPos(&x, &y);
	int w = Application::GetWindowWidth();
	int h = Application::GetWindowHeight();
	float worldX = (float)x * ObjectManager::Instance().WorldWidth / (float)w;
	float worldY = ((float)h - (float)y) * ObjectManager::Instance().WorldHeight / (float)h;

	SetMousePosition(Vector3(worldX, worldY - cIM_ScreenHeight, 0.f));

	std::map<MouseClick, MouseType>::iterator it = Mouse.begin();
	for (it; it != Mouse.end(); ++it)
	{
		if (it->second == MOUSE_RELEASE && Application::IsKeyPressed(VK_LBUTTON))
		{
			it->second = MOUSE_CLICK;
		}
		else if (it->second == MOUSE_CLICK && Application::IsKeyPressed(VK_LBUTTON))
		{
			it->second = MOUSE_HOLD;
		}
		else if ((it->second == MOUSE_HOLD || it->second == MOUSE_CLICK) && !Application::IsKeyPressed(VK_LBUTTON))
		{
			it->second = MOUSE_RELEASE;
		}
	}
}

void InputManager::SetMouseToScreenCenter()
{
	SetCursorPos((int)cIM_ScreenWidth / 2, (int)cIM_ScreenHeight / 2);
}