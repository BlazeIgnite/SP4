#include "Priest.h"
#include <iostream>
using std::cout;
using std::endl;

size_t PriestHealth[] = { 25, 25, 31, 34, 38, 38, 41, 47, 52, 59, 66, 71, 75, 81, 85, 90, 95, 103, 110, 125 };
size_t PriestAttack[] = { 13, 15, 15, 17, 19, 19, 21, 23, 25, 30, 33, 37, 43, 48, 50, 54, 55, 60, 63, 66 };
float PriestDefense[] = { 15, 15, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };


Priest::Priest()
{
	NormalAttackmultiplier = 0.40f;
	Name = "Priest";
}

Priest::~Priest()
{

}

void Priest::Init(int Level)
{
	if (Level > 0 && Level < 21)
	{
		SetLevel(Level);
		SetHealth(PriestHealth[Level - 1]);
		SetMaxHealth(PriestHealth[Level - 1]);
		SetAttack(PriestAttack[Level - 1]);
		SetDefense(PriestDefense[Level - 1]);
	}
	if (Level > 20)
	{
		float Levelscale = Level - 20;
		float finalscale = 1 + (Levelscale * 0.01f);
		SetLevel(Level);
		SetHealth((PriestHealth[19] * finalscale));
		SetMaxHealth(PriestHealth[19] * finalscale);
		SetAttack(PriestAttack[19] * finalscale);
		SetDefense(PriestDefense[19] * finalscale);
	}
	//SetPosition(Position_Middle);
	SetDamageMitigation();
}

void Priest::LevelUp()
{
	Level++;
	SetHealth(PriestHealth[Level]);
	SetAttack(PriestAttack[Level]);
	SetDefense(PriestDefense[Level]);

	if (Level <= 10)
	{
		Skill* skill = new Skill();
		if (Level == 10)
		{
			skill->SetName("Guardian Angel");
			skill->SetActionCost(80);
			skill->SetMaxTurnCooldown(6);
			skill->SetStatusEffect(3, "Buff");
			skill->SetRequiredPosition(2, true);
			skill->SetRequiredPosition(3, true);
			for (int i = 0; i < 3; i++)
			{
				skill->SetSelectableTarget(i, true);
			}
			SkillList.push_back(skill);
		}
		else if (Level == 5)
		{
			skill->SetName("Divine Guidance");
			skill->SetActionCost(30);
			skill->SetMaxTurnCooldown(2);
			skill->SetStatusEffect(3, "Buff");
			for (int i = 0; i < 3; i++)
			{
				skill->SetRequiredPosition(i, true);
				skill->SetSelectableTarget(i, true);
			}
			SkillList.push_back(skill);
		}
		else if (Level == 4)
		{
			skill->SetName("Unholy Gift");
			skill->SetActionCost(35);
			skill->SetMaxTurnCooldown(1);
			skill->SetRequiredPosition(2, true);
			skill->SetRequiredPosition(3, true);
			for (int i = 0; i < 3; i++)
			{
				skill->SetSelectableTarget(i, true);
			}
			SkillList.push_back(skill);
		}
		else if (Level == 3)
		{
			skill->SetName("Esuna");
			skill->SetActionCost(40);
			skill->SetMaxTurnCooldown(2);
			for (int i = 0; i < 3; i++)
			{
				skill->SetRequiredPosition(i, true);
				skill->SetSelectableTarget(i, true);
			}
			SkillList.push_back(skill);
		}
		else if (Level == 1)
		{
			skill->SetName("Basic Attack");
			skill->SetActionCost(15);

			for (int i = 0; i < 3; i++)
			{
				skill->SetRequiredPosition(i, true);
				skill->SetSelectableTarget(i, true);
			}

			SkillList.push_back(skill);

			skill = new Skill();
			skill->SetName("Heal");
			skill->SetActionCost(25);
			for (int i = 0; i < 3; i++)
			{
				skill->SetRequiredPosition(i, true);
				skill->SetSelectableTarget(i, true);
			}

			SkillList.push_back(skill);
		}
	}

	for (vector<Skill*>::iterator it = SkillList.begin(); it != SkillList.end(); it++)
	{
		Skill* SkillItr = (*it);
		if (SkillItr->GetName() == "Unholy Gift")
			SkillItr->SetDamage((int)(GetAttack() * 0.5));
		else if (SkillItr->GetName() == "Heal")
			SkillItr->SetHeal((int)(GetAttack() * 0.45));
		else if (SkillItr->GetName() == "Basic Attack")
			SkillItr->SetDamage((int)(GetAttack() * 0.4));
	}
}

void Priest::Update(double dt)
{

}