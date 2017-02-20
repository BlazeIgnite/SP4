#include "Warrior.h"
#include "Skill.h"

#include <iostream>
using std::cout;
using std::endl;

float WarriorHealth[] = { 0, 25, 25, 31, 34, 38, 38, 41, 47, 52, 59, 66, 71, 75, 81, 85, 90, 95, 103, 110, 125 };
float WarriorAttack[] = { 0, 13, 15, 15, 17, 19, 19, 21, 23, 25, 30, 33, 37, 43, 48, 50, 54, 55, 60, 63, 66 };
float WarriorDefense[] = { 0.f, 3.0f, 3.8f, 4.6f, 5.4f, 6.2f, 7.0f, 7.8f, 8.6f, 9.4f, 10.2f, 11.0f, 11.9f, 12.8f, 13.7f, 14.6f, 15.5f, 17.f, 18.5f, 20.f, 25.f };

Warrior::Warrior()
{
}

Warrior::~Warrior()
{
}

void Warrior::Init(int Level)
{
	SetLevel(Level);
	SetHealth(WarriorHealth[Level]);
	SetAttack(WarriorAttack[Level]);
	SetDefense(WarriorDefense[Level]);
	SetDamageMitigation();
}
void Warrior::Update(double dt)
{
	
}

void Warrior::LevelUp()
{
	Skill* skill = new Skill();

	if (Level == 10)
	{
		// Skill()
		skill->SetName("Divine Execution");
		SkillList.push_back(skill);
	}
	else if (Level == 4)
	{

	}
	else if (Level == 2)
	{

	}
	else if (Level == 1)
	{

	}
}