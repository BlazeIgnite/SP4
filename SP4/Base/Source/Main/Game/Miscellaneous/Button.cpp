#include "Button.h"
#include "GL\glew.h"
#include "../Systems/EventSystem.h"
#include "../Mains/Application.h"
#include "../Scene/Scene_Assignment1.h"
#include "../Scene/MainMenu.h"
#include "../Systems/BattleSystem.h"
#include "../../Base/Source/Main/Engine/System/InputManager.h"
#include "../../Engine/System/SceneSystem.h"


Button::Button()
{
}


Button::~Button()
{
}

void Button::Init(Vector3 Position, Vector3 Scale, std::string type)
{
	x = 0;
	y = 0;
	
	this->type = type;
	ObjectManager::Instance().WorldHeight = 100.f;
	ObjectManager::Instance().WorldWidth = ObjectManager::Instance().WorldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	position = Position;
	scale = Scale;
	maxHeight = position.y + scale.y / 2;
	maxWidth = position.x + scale.x / 2;
	minHeight = position.y - scale.y / 2;
	minWidth = position.x - scale.x / 2;
	isPressed = false;
	isSelected = false;
	isTarget = false;
	isOpened = false;

	CurrentState = UNTOUCHED;
}

void Button::Update()
{
	if (isitHover() && (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK || InputManager::Instance().GetMouseState(MOUSE_L) == HOLD))
	{
		if (CurrentState == UNTOUCHED || CurrentState == RELEASE)
			CurrentState = CLICK;
		else if (CurrentState == CLICK)
			CurrentState = HOLD;
	}
	else
	{
		if (CurrentState == CLICK || CurrentState == HOLD)
			CurrentState = RELEASE;
		else if (CurrentState == RELEASE)
			CurrentState = UNTOUCHED;
	}
}


void Button::UpdateMainMenu(float dt)
{
	Application::GetCursorPos(&x, &y);
	isitHover();

	if (type == "NewGame" && isitHover())
	{
		if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK)
		{
			//SceneSystem::Instance().SwitchScene("Town_Scene");
		}
	}
	else if (type == "LoadGame" && isitHover())
	{
		if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK)
		{
		}
	}
	else if (type == "Setting" && isitHover())
	{
		if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK)
		{
		}
	}
	else if (type == "ExitGame" && isitHover())
	{
		if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK)
		{
			
		}
	}
	else if (type == "File1" && isitHover())
	{
		if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK)
		{
		}
	}
	else if (type == "File2" && isitHover())
	{
		if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK)
		{

		}
	}
	else if (type == "File3" && isitHover())
	{
		if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK)
		{

		}
	}
	
}

void Button::UpdateBattleScene(float dt)
{
	Application::GetCursorPos(&x, &y);
	isitHover();
	//Consumables
	if (type == "Red Potion" && isitHover())
	{
		if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK)
		{
			if (!isPressed)
			{
				if ((Player::Instance().GetConsumableList().find("Red Potion")->second > 0) && (BattleSystem::Instance().GetSelectedTroop()->GetHealth() >= BattleSystem::Instance().GetSelectedTroop()->GetMaxHealth() ))
				{
					Player::Instance().AddConsumableItem("Red Potion", -1);
					BattleSystem::Instance().GetSelectedTroop()->SetHealth(BattleSystem::Instance().GetSelectedTroop()->GetHealth() + 20);
					BattleSystem::Instance().GetSelectedTroop()->GetMaxHealth();
					std::cout << "Red Potion Used" << std::endl;
					isPressed = true;
				}
				else
				{
					std::cout << "No More Red Potion" << std::endl;
					isPressed = true;
				}
			}
		}
		else
		{
			if (isPressed)
				isPressed = false;
		}
	}
	if (type == "Attack Potion" && isitHover())
	{
		if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK)
		{
			if ((Player::Instance().GetConsumableList().find("Attack Potion")->second > 0) && (BattleSystem::Instance().GetSelectedTroop()->GetHealth() >= BattleSystem::Instance().GetSelectedTroop()->GetMaxHealth()))
			{
				Player::Instance().AddConsumableItem("Attack Potion", -1);
				BattleSystem::Instance().GetSelectedTroop()->SetHealth(BattleSystem::Instance().GetSelectedTroop()->GetHealth() + 20);
				BattleSystem::Instance().GetSelectedTroop()->GetMaxHealth();
				std::cout << "Attack Potion Used" << std::endl;
				isPressed = true;
			}
			else
			{
				std::cout << "No More Attack Potion" << std::endl;
				isPressed = true;
			}
		}
	}

	if (type == "Defence Potion" && isitHover())
	{
		if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK)
		{
			if ((Player::Instance().GetConsumableList().find("Defence Potion")->second > 0) && (BattleSystem::Instance().GetSelectedTroop()->GetHealth() >= BattleSystem::Instance().GetSelectedTroop()->GetMaxHealth()))
			{
				Player::Instance().AddConsumableItem("Defence Potion", -1);
				BattleSystem::Instance().GetSelectedTroop()->SetHealth(BattleSystem::Instance().GetSelectedTroop()->GetHealth() + 20);
				BattleSystem::Instance().GetSelectedTroop()->GetMaxHealth();
				std::cout << "Defence Potion Used" << std::endl;
				isPressed = true;
			}
			else
			{
				std::cout << "No More Defence Potion" << std::endl;
				isPressed = true;
			}
		}
		else
		{
			if (isPressed)
				isPressed = false;
		}
	}

	if (type == "Bandage" && isitHover())
	{
		if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK)
		{
			if ((Player::Instance().GetConsumableList().find("Bandage")->second > 0) && (BattleSystem::Instance().GetSelectedTroop()->GetHealth() >= BattleSystem::Instance().GetSelectedTroop()->GetMaxHealth()))
			{
				Player::Instance().AddConsumableItem("Bandage", -1);
				BattleSystem::Instance().GetSelectedTroop()->SetHealth(BattleSystem::Instance().GetSelectedTroop()->GetHealth() + 20);
				BattleSystem::Instance().GetSelectedTroop()->GetMaxHealth();
				std::cout << "Bandage Used" << std::endl;
				isPressed = true;
			}
			else
			{
				std::cout << "No More Bandage" << std::endl;
				isPressed = true;
			}
		}
	}
	//Skills and Auto Attack

	if (type == "Auto Attack" && isitHover())
	{
		if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK)
		{
		}
	}

	if (type == "Skill 1" && isitHover())
	{
		if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK)
		{
		}
	}

	if (type == "Skill 2" && isitHover())
	{
		if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK)
		{
		}
	}

	if (type == "Skill 3" && isitHover())
	{
		if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK)
		{
		}
	}

}

void Button::UpdateCrafting(float dt)
{
	Application::GetCursorPos(&x, &y);
	isitHover();

	if (type == "Red Potion" && isitHover())
	{
		if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK)
		{
			if ((Player::Instance().GetMaterialList().find("Red Herb")->second > 1) && (Player::Instance().GetMaterialList().find("Empty Bottle")->second > 0))
			{
				Player::Instance().AddMaterialItem("Red Herb", -2);
				Player::Instance().AddMaterialItem("Empty Bottle", -1);
				Player::Instance().AddConsumableItem("Red Potion", 1);
				std::cout << "Red Potion Crafted" << std::endl;
				isPressed = true;
			}
			else
			{
				std::cout << "Not Enough Materials" << std::endl;
				isPressed = true;
			}
		}
	}

	/*if (type == "Blue Potion" && isitHover())
	{
		if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK)
		{
			if (!isPressed)
			{
				if ((Player::Instance().GetMaterialList().find("Blue Herb")->second > 1) && (Player::Instance().GetMaterialList().find("Empty Bottle")->second > 0))
				{
					Player::Instance().AddMaterialItem("Blue Herb", -2);
					Player::Instance().AddMaterialItem("Empty Bottle", -1);
					Player::Instance().AddConsumableItem("Blue Potion", 1);
					std::cout << "Blue Potion Crafted" << std::endl;
					isPressed = true;
				}
				else
				{
					std::cout << "Not Enough Materials" << std::endl;
					isPressed = true;
				}
			}
		}
		else
		{
			isPressed = false;
		}
	}*/

	if (type == "Attack Potion" && isitHover())
	{
		if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK)
		{
				if ((Player::Instance().GetMaterialList().find("White Herb")->second > 0) && (Player::Instance().GetMaterialList().find("Red Herb")->second > 2) && (Player::Instance().GetMaterialList().find("Empty Bottle")->second > 0))
				{
					Player::Instance().AddMaterialItem("White Herb", -1);
					Player::Instance().AddMaterialItem("Red Herb", -3);
					Player::Instance().AddMaterialItem("Empty Bottle", -1);
					Player::Instance().AddConsumableItem("Attack Potion", 1);
					std::cout << "Attack Potion Crafted" << std::endl;
				}
				else
				{
					std::cout << "Not Enough Materials" << std::endl;
				}
		}
	}

	if (type == "Defence Potion" && isitHover())
	{
		if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK)
		{
				if ((Player::Instance().GetMaterialList().find("White Herb")->second > 0) && (Player::Instance().GetMaterialList().find("Blue Herb")->second > 2) && (Player::Instance().GetMaterialList().find("Empty Bottle")->second > 0))
				{
					Player::Instance().AddMaterialItem("White Herb", -1);
					Player::Instance().AddMaterialItem("Blue Herb", -3);
					Player::Instance().AddMaterialItem("Empty Bottle", -1);
					Player::Instance().AddConsumableItem("Defence Potion", 1);
					std::cout << "Defence Potion Crafted" << std::endl;
					isPressed = true;
				}
				else
				{
					std::cout << "Not Enough Materials" << std::endl;
					isPressed = true;
				}
		}
	}

	if (type == "Bandage" && isitHover())
	{
		if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK)
		{
				if (Player::Instance().GetMaterialList().find("Cloth")->second > 2)
				{
					Player::Instance().AddMaterialItem("Cloth", -3);
					Player::Instance().AddConsumableItem("Bandage", 1);
					std::cout << "Bandage Crafted" << std::endl;
					isPressed = true;
				}
				else
				{
					std::cout << "Not Enough Materials" << std::endl;
					isPressed = true;
				}
		}
	}
	
	//Crafting Page
}

bool Button::isitHover()
{
	float worldX = InputManager::Instance().GetMousePosition().x;
	float worldY = InputManager::Instance().GetMousePosition().y;

	if (worldY > minHeight && worldY < maxHeight)
	{
		if (worldX > minWidth && worldX < maxWidth)
			return true;
		else
			return false;
	}
	else
		return false;
	
}

bool Button::GetisPressed()
{
	return isPressed;
}

bool Button::GetisSelected()
{
	return isSelected;
}

bool Button::GetisTarget()
{
	return isTarget;
}

Vector3 Button::GetPosition()
{
	return position;
}

Vector3 Button::GetScale()
{
	return scale;
}

void Button::SetisPressed(bool pressed)
{
	this->isPressed = pressed;
}

void Button::SetisSelected(bool select)
{
	this->isSelected = select;
}

void Button::SetisTarget(bool target)
{
	this->isTarget = target;
}

STATE Button::GetCurrentState()
{
	return this->CurrentState;
}