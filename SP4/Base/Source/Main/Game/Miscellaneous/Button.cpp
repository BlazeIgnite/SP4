#include "Button.h"
#include "GL\glew.h"
#include "../Systems/EventSystem.h"
#include "../Mains/Application.h"
#include "../Scene/Scene_Assignment1.h"
#include "../Systems/BattleSystem.h"


Button::Button()
{
}


Button::~Button()
{
}

void Button::Init(Vector3 Position, Vector3 Scale, std::string type, Player* player)
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
	this->player = player;
	
}

void Button::Update(double dt)
{
	Application::GetCursorPos(&x, &y);
	isitHover();

	//Put into Crafting Page
	if (type == "Red Potion" && isitHover())
	{
		if (Application::IsMousePressed(0))
		{
			if (!isPressed)
			{
				if ((player->GetMaterialList().find("Red Herb")->second > 1) && (player->GetMaterialList().find("Empty Bottle")->second > 0))
				{
					player->AddMaterialItem("Red Herb", -2);
					player->AddMaterialItem("Empty Bottle", -1);
					player->AddConsumableItem("Red Potion", 1);
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
	}
	else if (type == "Blue Potion" && isitHover())
	{
		if (Application::IsMousePressed(0))
		{
			if (!isPressed)
			{
				if ((player->GetMaterialList().find("Blue Herb")->second > 1) && (player->GetMaterialList().find("Empty Bottle")->second > 0))
				{
					player->AddMaterialItem("Blue Herb", -2);
					player->AddMaterialItem("Empty Bottle", -1);
					player->AddConsumableItem("Blue Potion", 1);
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
	}
	else if (type == "Attack Potion" && isitHover())
	{
		if (Application::IsMousePressed(0))
		{
			if (!isPressed)
			{
				if ((player->GetMaterialList().find("White Herb")->second > 0) && (player->GetMaterialList().find("Red Herb")->second > 2) && (player->GetMaterialList().find("Empty Bottle")->second > 0))
				{
					player->AddMaterialItem("White Herb", -1);
					player->AddMaterialItem("Red Herb", -3);
					player->AddMaterialItem("Empty Bottle", -1);
					player->AddConsumableItem("Attack Potion", 1);
					std::cout << "Attack Potion Crafted" << std::endl;
					isPressed = true;
				}
				else
				{
					std::cout << "Not Enough Materials" << std::endl;
					isPressed = true;
				}
			}
		}
	}
	else if (type == "Defense Potion" && isitHover())
	{
		if (Application::IsMousePressed(0))
		{
			if (!isPressed)
			{
				if ((player->GetMaterialList().find("White Herb")->second > 0) && (player->GetMaterialList().find("Blue Herb")->second > 2) && (player->GetMaterialList().find("Empty Bottle")->second > 0))
				{
					player->AddMaterialItem("White Herb", -1);
					player->AddMaterialItem("Blue Herb", -3);
					player->AddMaterialItem("Empty Bottle", -1);
					player->AddConsumableItem("Defense Potion", 1);
					std::cout << "Defense Potion Crafted" << std::endl;
					isPressed = true;
				}
				else
				{
					std::cout << "Not Enough Materials" << std::endl;
					isPressed = true;
				}
			}
		}
	}
	else if (type == "Bandage" && isitHover())
	{
		if (Application::IsMousePressed(0))
		{
			if (!isPressed)
			{
				if (player->GetMaterialList().find("Cloth")->second > 2)
				{
					player->AddMaterialItem("Cloth", -3);
					player->AddConsumableItem("Bandage", 1);
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
	}
	else
	{
		isPressed = false;
	}
	//Crafting Page
}

bool Button::isitHover()
{
	int w = Application::GetWindowWidth();
	int h = Application::GetWindowHeight();
	float worldX = (float)x * ObjectManager::Instance().WorldWidth / (float)w;
	float worldY = ((float)h - (float)y) * ObjectManager::Instance().WorldHeight / (float)h;

	//std::cout << minHeight << " " << maxHeight << " " << worldY << std::endl;
	//std::cout << minWidth << " " << maxWidth << " " << worldX << std::endl;
	if (worldY > minHeight && worldY < maxHeight)
	{
		if (worldX > minWidth && worldX < maxWidth)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

Vector3 Button::GetPosition()
{
	return position;
}

Vector3 Button::GetScale()
{
	return scale;
}