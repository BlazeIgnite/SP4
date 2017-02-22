#include "InputManager.h"
#include "../../Game/Mains/Application.h"
#include "SceneSystem.h"
#include "SimpleCommand.h"
#include "../../Base/Source/Main/Game/Systems/ObjectManager.h"
#include <locale>

InputManager::InputManager()
{
	for (int num = 0; num < 256; ++num)
	{
		cIM_Keys[num] = false;
	}
	Mouse = std::map<MouseClick, Type>();
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

InputManager::Type InputManager::GetMouseState(MouseClick Click)
{
	std::map<MouseClick, Type>::iterator it = Mouse.find(Click);
	if (it == Mouse.end())
	{
		Mouse.insert(std::pair<MouseClick, Type>(Click, RELEASE));
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

	std::map<MouseClick, Type>::iterator it = Mouse.begin();
	for (it; it != Mouse.end(); ++it)
	{
		if (it->first == MOUSE_L)
		{
			if ((it->second == RELEASE || it->second == UNTOUCHED) && Application::IsKeyPressed(VK_LBUTTON))
				it->second = CLICK;
			else if (it->second == CLICK && Application::IsKeyPressed(VK_LBUTTON))
				it->second = HOLD;
			else if ((it->second == HOLD || it->second == CLICK) && !Application::IsKeyPressed(VK_LBUTTON))
				it->second = RELEASE;
			else if (it->second == RELEASE && !Application::IsKeyPressed(VK_LBUTTON))
				it->second = UNTOUCHED;
		}
		if (it->first == MOUSE_R)
		{
			if ((it->second == RELEASE || it->second == UNTOUCHED) && Application::IsKeyPressed(VK_RBUTTON))
				it->second = CLICK;
			else if (it->second == CLICK && Application::IsKeyPressed(VK_RBUTTON))
				it->second = HOLD;
			else if ((it->second == HOLD || it->second == CLICK) && !Application::IsKeyPressed(VK_RBUTTON))
				it->second = RELEASE;
			else if (it->second == RELEASE && !Application::IsKeyPressed(VK_RBUTTON))
				it->second = UNTOUCHED;
		}
	}
}

void InputManager::SetMouseToScreenCenter()
{
	SetCursorPos((int)cIM_ScreenWidth / 2, (int)cIM_ScreenHeight / 2);
}

void InputManager::KeyboardInput()
{
	int NumberOffset = 48;
	int AlphabetOffset = 65;
	int CapsValue;
	for (int Number = 0; Number <= 10; ++Number)
		if (Application::IsKeyPressed(Number + NumberOffset))
			CheckKeyPressed(Number + NumberOffset);
	for (int Alphabet = 0; Alphabet <= 25; ++Alphabet)
		if (Application::IsKeyPressed(Alphabet + AlphabetOffset))
			CheckKeyPressed(Alphabet + AlphabetOffset);
	if (Application::IsKeyPressed(VK_SPACE))
		CheckKeyPressed(VK_SPACE);
	if (Application::IsKeyPressed(VK_BACK))
		CheckKeyPressed(VK_BACK);
}

char InputManager::GetKeyPressed()
{
	for (std::map<char, InputManager::Type>::iterator Keyit = KeyInput.begin(); Keyit != KeyInput.end(); ++Keyit)
		if (Keyit->second == CLICK)
			return Keyit->first;
	return NULL;
}

void InputManager::KeyPressedUpdate()
{
	for (std::map<char, InputManager::Type>::iterator Keyit = KeyInput.begin(); Keyit != KeyInput.end(); ++Keyit)
	{
		if ((Keyit->second == RELEASE || Keyit->second == UNTOUCHED) && Application::IsKeyPressed(toupper(Keyit->first)))
			Keyit->second = CLICK;
		else if (Keyit->second == CLICK && Application::IsKeyPressed(toupper(Keyit->first)))
			Keyit->second = HOLD;
		else if ((Keyit->second == CLICK || Keyit->second == HOLD) && !Application::IsKeyPressed(toupper(Keyit->first)))
			Keyit->second = RELEASE;
		else if (Keyit->second == RELEASE && !Application::IsKeyPressed(toupper(Keyit->first)))
			Keyit->second = UNTOUCHED;
	}
	KeyboardInput();
}

InputManager::Type InputManager::CheckKeyPressed(char key)
{
	std::map<char, InputManager::Type>::iterator Keyit = KeyInput.find(key);
	if (Keyit == KeyInput.end())
	{
		KeyInput.insert(std::pair<char, InputManager::Type>(key, CLICK));
		return CLICK;
	}
	return Keyit->second;
}

void InputManager::Update()
{
	UpdateMouse();
	KeyPressedUpdate();
}