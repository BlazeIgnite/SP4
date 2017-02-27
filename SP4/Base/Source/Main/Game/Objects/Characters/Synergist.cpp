#include "Synergist.h"
#include <iostream>
using std::cout;
using std::endl;

size_t SynergistHealth[] = { 0, 25, 25, 31, 34, 38, 38, 41, 47, 52, 59, 66, 71, 75, 81, 85, 90, 95, 103, 110, 125 };
size_t SynergistAttack[] = { 0, 13, 15, 15, 17, 19, 19, 21, 23, 25, 30, 33, 37, 43, 48, 50, 54, 55, 60, 63, 66 };
float SynergistDefence[] = { 0, 15, 15, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };

Synergist::Synergist()
{
	NormalAttackmultiplier = 0.40f;
	Name = "Synergist";
}

Synergist::~Synergist()
{

}

void Synergist::Init(int Level)
{
	SetisPressed(false);
	SetisSelected(false);
	//if (Level > 0 && Level < 21)
	//{
	//	SetLevel(Level);
	//	SetHealth(SynergistHealth[Level - 1]);
	//	SetMaxHealth(SynergistHealth[Level - 1]);
	//	SetAttack(SynergistAttack[Level - 1]);
	//	SetDefence(SynergistDefence[Level - 1]);
	//}
	//if (Level > 20)
	//{
	//	float Levelscale = Level - 20;
	//	float finalscale = 1 + (Levelscale * 0.01f);
	//	SetLevel(Level);
	//	SetHealth((SynergistHealth[19] * finalscale));
	//	SetMaxHealth(SynergistHealth[19] * finalscale);
	//	SetAttack(SynergistAttack[19] * finalscale);
	//	SetDefence(SynergistDefence[19] * finalscale);
	//}
	////SetPosition(Position_Middle);
	for (int i = 0; i < Level; i++)
	{
		LevelUp();
	}
}

void Synergist::LevelUp()
{
	Level++;
	SetHealth(SynergistHealth[Level]);
	SetMaxHealth(SynergistHealth[Level]);
	SetAttack(SynergistAttack[Level]);
	SetDefence(SynergistDefence[Level]);
	SetDamageMitigation();

	if (Level <= 10)
	{
		Skill* skill = new Skill();
		if (Level == 10)
		{
			skill->SetName("Quake");
			skill->SetActionCost(60);
			skill->SetMaxTurnCooldown(6);
			skill->SetStatusEffect(4, "Stun");
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
			skill->SetName("Power Breakdown");
			skill->SetActionCost(30);
			skill->SetMaxTurnCooldown(4);
			skill->SetStatusEffect(3, "Debuff");
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
			skill->SetName("Dark Hail");
			skill->SetActionCost(40);
			skill->SetMaxTurnCooldown(2);
			skill->SetStatusEffect(2,"Stun");
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
			skill->SetName("Life Drain");
			skill->SetActionCost(25);
			skill->SetStatusEffect(2, "Debuff");
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
			SkillItr->SetDamage((int)(Attack * 0.5));
		else if (SkillItr->GetName() == "Life Drain")
			SkillItr->SetDamage((int)(Attack * 0.3));
		else if (SkillItr->GetName() == "Dark Hail")
			SkillItr->SetDamage((int)(Attack*0.3));
		else if (SkillItr->GetName() == "Basic Attack")
			SkillItr->SetDamage((int)(Attack * 0.4));
	}
}

void Synergist::Update(double dt)
{

}