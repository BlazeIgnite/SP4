#include "Warrior.h"
#include "Skill.h"

#include <iostream>
using std::cout;
using std::endl;

size_t WarriorHealth[] = { 0, 25, 25, 31, 34, 38, 38, 41, 47, 52, 59, 66, 71, 75, 81, 85, 90, 95, 103, 110, 125 };
size_t WarriorAttack[] = { 0, 13, 15, 15, 17, 19, 19, 21, 23, 25, 30, 33, 37, 43, 48, 50, 54, 55, 60, 63, 66 };
float WarriorDefense[] = { 0.f, 3.0f, 3.8f, 4.6f, 5.4f, 6.2f, 7.0f, 7.8f, 8.6f, 9.4f, 10.2f, 11.0f, 11.9f, 12.8f, 13.7f, 14.6f, 15.5f, 17.f, 18.5f, 20.f, 25.f };

Warrior::Warrior()
{
	NormalAttackmultiplier = 0.75f;
}

Warrior::~Warrior()
{
	for (vector<Skill*>::iterator it = SkillList.begin(); it != SkillList.end(); it++)
	{
		if ((*it) != nullptr)
		{
			delete (*it);
			(*it) = nullptr;
		}
	}
}

void Warrior::Init(int Level)
{
	if (Level > 0 && Level < 21)
	{
		SetLevel(Level);
		SetHealth(WarriorHealth[Level]);
		SetAttack(WarriorAttack[Level]);
		SetDefense(WarriorDefense[Level]);
		SetDamageMitigation();
	}
	
	//This Section is so that AI levels that Exceed Level 20 will be Scaled;
	if (Level > 20)
	{
		SetLevel(Level);
		float LevelOffset = (Level - 20) / 100;
		SetHealth(WarriorHealth[19] * (1 + LevelOffset));
		SetAttack(WarriorAttack[19] * (1 + LevelOffset));
		SetDefense(WarriorDefense[19] * (1 + LevelOffset));
		SetDamageMitigation();
	}
}
void Warrior::Update(double dt)
{
	
}

void Warrior::LevelUp()
{
	if (Level <= 10)
	{
		if (Level == 10)
		{
			// Divine Execution
			Skill* skill = new Skill();
			skill->SetName("Divine Execution");
			skill->SetActionCost(85);
			skill->SetMaxTurnCooldown(5);
			skill->SetRequiredPosition(0, 0);
			SkillList.push_back(skill);
		}
		else if (Level == 4)
		{
			// Taunt Skill
			Skill* skill = new Skill();
			skill->SetName("Taunt");
			skill->SetActionCost(35);
			skill->SetMaxTurnCooldown(2);
			skill->SetStatusEffect(1, "Buff");
			//skill->

			// 
			skill = new Skill();
		}
		else if (Level == 2)
		{
			Skill* skill = new Skill();
		}
	}

	for (vector<Skill*>::iterator it = SkillList.begin(); it != SkillList.end(); it++)
	{
		Skill* SkillItr = (*it);
		if (SkillItr->GetName() == "Rush")
			SkillItr->SetDamage(GetAttack() * 0.3);
		else if (SkillItr->GetName() == "Bash")
			SkillItr->SetDamage(GetAttack() * 0.3);
		else if (SkillItr->GetName() == "Divine Execution")
			SkillItr->SetDamage(GetAttack() * 1.5);
	}

}