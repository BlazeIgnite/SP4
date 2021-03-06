#include "Button.h"
#include "GL\glew.h"
#include "../Systems/EventSystem.h"
#include "../Mains/Application.h"
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

	CurrentState = UNTOUCHED;
	CurrentStateR = UNTOUCHED;
}

void Button::Update()
{
	if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK || InputManager::Instance().GetMouseState(MOUSE_L) == HOLD)
	{
		if (isitHover())
		{
			isSelected = true;
			if (CurrentState == UNTOUCHED || CurrentState == RELEASE)
				CurrentState = CLICK;
			else if (CurrentState == CLICK)
				CurrentState = HOLD;
		}
		else
		{
			isSelected = false;
			if (CurrentState == CLICK || CurrentState == HOLD)
				CurrentState = RELEASE;
			else if (CurrentState == RELEASE)
				CurrentState = UNTOUCHED;
		}
	}
	else
	{
		if (CurrentState == CLICK || CurrentState == HOLD)
			CurrentState = RELEASE;
		else if (CurrentState == RELEASE)
			CurrentState = UNTOUCHED;
	}
	if (InputManager::Instance().GetMouseState(MOUSE_R) == CLICK || InputManager::Instance().GetMouseState(MOUSE_R) == HOLD)
	{
		if (isitHover())
		{
			isSelected = false;
			if (CurrentStateR == UNTOUCHED || CurrentStateR == RELEASE)
				CurrentStateR = CLICK;
			else if (CurrentStateR == CLICK)
				CurrentStateR = HOLD;
		}
		else
		{
			if (CurrentStateR == CLICK || CurrentStateR == HOLD)
				CurrentStateR = RELEASE;
			else if (CurrentStateR == RELEASE)
				CurrentStateR = UNTOUCHED;
		}
	}
	else
	{
		if (CurrentStateR == CLICK || CurrentStateR == HOLD)
			CurrentStateR = RELEASE;
		else if (CurrentStateR == RELEASE)
			CurrentStateR = UNTOUCHED;
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
			if ((Player::Instance().GetConsumableList().find("Red Potion")->second > 0) && (BattleSystem::Instance().GetSelectedTroop()->GetHealth() < BattleSystem::Instance().GetSelectedTroop()->GetMaxHealth() ))
			{
				Player::Instance().AddConsumableItem("Red Potion", -1);
				size_t temp = BattleSystem::Instance().GetSelectedTroop()->GetHealth() + 50;
				if (temp > BattleSystem::Instance().GetSelectedTroop()->GetMaxHealth())
					temp = BattleSystem::Instance().GetSelectedTroop()->GetMaxHealth();
				BattleSystem::Instance().GetSelectedTroop()->SetHealth(temp);
			}
		}
	}
	if (type == "Attack Potion" && isitHover())
	{
		if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK)
		{
			if ((Player::Instance().GetConsumableList().find("Attack Potion")->second > 0))
			{
				Player::Instance().AddConsumableItem("Attack Potion", -1);
				BattleSystem::Instance().GetSelectedTroop()->SetAttack(BattleSystem::Instance().GetSelectedTroop()->GetAttack() + 20);
				isPressed = true;
			}
			else
			{
				isPressed = true;
			}
		}
	}

	if (type == "Defence Potion" && isitHover())
	{
		if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK)
		{
			if ((Player::Instance().GetConsumableList().find("Defence Potion")->second > 0) )
			{
				Player::Instance().AddConsumableItem("Defence Potion", -1);
				BattleSystem::Instance().GetSelectedTroop()->SetDefence(BattleSystem::Instance().GetSelectedTroop()->GetDefence() + 20);
				isPressed = true;
			}
			else
			{
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
			if ((Player::Instance().GetConsumableList().find("Bandage")->second > 0))
			{
				Player::Instance().AddConsumableItem("Bandage", -1);
				BattleSystem::Instance().GetSelectedTroop()->SetDebuffed(false);
				isPressed = true;
			}
			else
			{
				isPressed = true;
			}
		}
	}
}

void Button::UpdateCrafting(float dt)
{
	Application::GetCursorPos(&x, &y);
	isitHover();
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