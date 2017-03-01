#include "BattleButton.h"
#include "../../Base/Source/Main/Engine/System/SceneSystem.h"
#include "../../Base/Source/Main/Engine/System/RenderSystem.h"
#include "../../Mains/Application.h"
#include "../../Game/Systems/BattleSystem.h"

BattleButton::BattleButton()
{
}


BattleButton::~BattleButton()
{
}

void BattleButton::Init(double x, double y)
{
	Button* temp;
	temp = new Button();
	temp->Init(Vector3(55, 22.5, 0), Vector3(10, 10, 1), "Character 1");
	buttonList.push_back(temp);
	temp = new Button();
	temp->Init(Vector3(35, 22.5, 0), Vector3(10, 10, 1), "Character 2");
	buttonList.push_back(temp);
	temp = new Button();
	temp->Init(Vector3(15, 22.5, 0), Vector3(10, 10, 1), "Character 3");
	buttonList.push_back(temp);

	temp = new Button();
	temp->Init(Vector3(17.5, 20, 0), Vector3(7, 7, 1), "Red Potion");
	buttonList.push_back(temp);
	temp = new Button();
	temp->Init(Vector3(27.5, 20, 0), Vector3(7, 7, 1), "Bandage");
	buttonList.push_back(temp);
	temp = new Button();
	temp->Init(Vector3(37.5, 20, 0), Vector3(7, 7, 1), "Attack Potion");
	buttonList.push_back(temp);
	temp = new Button();
	temp->Init(Vector3(47.5, 20, 0), Vector3(7, 7, 1), "Defence Potion");
	buttonList.push_back(temp);

	temp = new Button();
	temp->Init(Vector3(68, 15, 0), Vector3(6, 6, 1), "Default Attack");
	buttonList.push_back(temp);
	temp = new Button();
	temp->Init(Vector3(82, 15, 0), Vector3(6, 6, 1), "Skill 1");
	buttonList.push_back(temp);
	temp = new Button();
	temp->Init(Vector3(96, 15, 0), Vector3(6, 6, 1), "Skill 2");
	buttonList.push_back(temp);
	temp = new Button();
	temp->Init(Vector3(110, 15, 0), Vector3(6, 6, 1), "Skill 3");
	buttonList.push_back(temp);
	temp = new Button();
	temp->Init(Vector3(140, 15, 0), Vector3(17, 7, 1), "Attack Button");
	buttonList.push_back(temp);
	temp = new Button();
	temp->Init(Vector3(160, 15, 0), Vector3(17, 7, 1), "End Turn");
	buttonList.push_back(temp);

	temp = new Button();
	temp->Init(Vector3(120, 22.5, 0), Vector3(10, 10, 1), "AI 1");
	buttonList.push_back(temp);
	temp = new Button();
	temp->Init(Vector3(140, 22.5, 0), Vector3(10, 10, 1), "AI 2");
	buttonList.push_back(temp);
	temp = new Button();
	temp->Init(Vector3(160, 22.5, 0), Vector3(10, 10, 1), "AI 3");
	buttonList.push_back(temp);

	temp->SetisPressed(false);
	temp->SetisSelected(false);
	temp->SetisTarget(false);

	Description* temp2;
	temp2 = new Description();
	temp2->Init(Vector3(x, y, 0), Vector3(14, 10, 1), "Default Attack");
	descripList.push_back(temp2);
	temp2 = new Description();
	temp2->Init(Vector3(x, y, 0), Vector3(14, 10, 1), "Skill 1");
	descripList.push_back(temp2);
	temp2 = new Description();
	temp2->Init(Vector3(x, y, 0), Vector3(14, 10, 1), "Skill 2");
	descripList.push_back(temp2);
	temp2 = new Description();
	temp2->Init(Vector3(x, y, 0), Vector3(14, 10, 1), "Skill 3");
	descripList.push_back(temp2);
}

void BattleButton::Update(float dt)
{
	
}

void BattleButton::UpdateDescription(float dt)
{
	for (std::vector<Description*>::iterator itr2 = descripList.begin(); itr2 != descripList.end(); itr2++)
		{
			(*itr2)->Update(dt);
		}
}

void BattleButton::Exit()
{
	for (std::vector<Button*>::iterator it = buttonList.begin(); it != buttonList.end(); it++)
	{
		if ((*it) != nullptr)
		{
			delete (*it);
			(*it) = nullptr;
		}
	}
}

std::vector<Button*>* BattleButton::GetList()
{
	return &buttonList;
}

std::vector<Description*>* BattleButton::GetDescriList()
{
	return &descripList;
}