#include "BattleButton.h"


BattleButton::BattleButton()
{
}


BattleButton::~BattleButton()
{
}

void BattleButton::Init()
{
	Character1 = new Button();
	Character1->Init(Vector3(75, 50, 0), Vector3(10, 10, 1), "Character 1");
	Character2 = new Button();
	Character2->Init(Vector3(75, 50, 0), Vector3(10, 10, 1), "Character 2");
	Character3 = new Button();
	Character3->Init(Vector3(75, 50, 0), Vector3(10, 10, 1), "Character 3");

	RedPotion = new Button();
	RedPotion->Init(Vector3(75, 50, 0), Vector3(10, 10, 1), "Red Potion");
	BluePotion = new Button();
	BluePotion->Init(Vector3(75, 50, 0), Vector3(10, 10, 1), "Blue Potion");
	AttackPotion = new Button();
	AttackPotion->Init(Vector3(75, 50, 0), Vector3(10, 10, 1), "Attack Potion");
	DefencePotion = new Button();
	DefencePotion->Init(Vector3(75, 50, 0), Vector3(10, 10, 1), "Defence Potion");
	Bandage = new Button();
	Bandage->Init(Vector3(75, 50, 0), Vector3(10, 10, 1), "Bandage");


	Skill1 = new Button();
	Skill1->Init(Vector3(75, 50, 0), Vector3(10, 10, 1), "Skill1");
	Skill2 = new Button();
	Skill2->Init(Vector3(75, 50, 0), Vector3(10, 10, 1), "Skill2");
	Skill3 = new Button();
	Skill3->Init(Vector3(75, 50, 0), Vector3(10, 10, 1), "Skill3");


	AI1 = new Button();
	AI1->Init(Vector3(75, 50, 0), Vector3(10, 10, 1), "AI1");
	AI2 = new Button();
	AI2->Init(Vector3(75, 50, 0), Vector3(10, 10, 1), "AI2");
	AI3 = new Button();
	AI3->Init(Vector3(75, 50, 0), Vector3(10, 10, 1), "AI3");
}

void BattleButton::Update(float dt)
{
	for (std::vector<Button*>::iterator itr = buttonList.begin(); itr != buttonList.end(); itr++)
	{
		(*itr)->Update(dt);
	}
}
