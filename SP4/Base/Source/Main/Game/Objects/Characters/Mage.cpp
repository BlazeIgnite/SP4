#include "Mage.h"
#include <iostream>
using std::cout;
using std::endl;

float MageHealth[] = { 25, 25, 31, 34, 38, 38, 41, 47, 52, 59, 66, 71, 75, 81, 85, 90, 95, 103, 110, 125 };
float MageAbilityPoints[] = { 15, 15, 15, 20, 24, 27, 31, 32, 34, 37, 38, 39, 41, 43, 46, 50, 51, 53, 55, 60 };
float MageAttack[] = { 13, 15, 15, 17, 19, 19, 21, 23, 25, 30, 33, 37, 43, 48, 50, 54, 55, 60, 63, 66 };
float MageDefense[] = { 15, 15, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };
float MageMagic[] = { 2, 15, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };
float MageLuck[] = { 1, 15, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };


Mage::Mage()
{
	NormalAttackmultiplier = 0.50f;
}

Mage::~Mage()
{

}

void Mage::Init(int Level)
{
	if (Level > 0 && Level < 21)
	{
		SetLevel(Level);
		SetHealth(MageHealth[Level - 1]);
		SetMaxHealth(MageHealth[Level - 1]);
		SetAttack(MageAttack[Level - 1]);
		SetDefense(MageDefense[Level - 1]);
	}
	if (Level > 20)
	{
		float Levelscale = Level - 20;
		float finalscale = 1 + (Levelscale * 0.01f);
		SetLevel(Level);
		SetHealth((MageHealth[19] * finalscale));
		SetMaxHealth(MageHealth[19] * finalscale);
		SetAttack(MageAttack[19] * finalscale);
		SetDefense(MageDefense[19] * finalscale);
	}
//	SetPosition(Position_Back);
	SetDamageMitigation();

/*

	skill_1 = new OffensiveSkill();
	skill_1->SetSkill_IDs("Magic Bolt", 1);
	skill_1->SetAbilityCost(5);
	skill_1->SetMultiplier(0.65f);
	skill_1->SetActionCost(20.f);
	skill_1->SetScaleFactor(Skill::Scale_Magic);
	skill_1->shiftposition = 0;*/
}

void Mage::LevelUp()
{
	if (Level <= 10)
	{
		Skill* skill = new Skill();
		if (Level == 10)
		{
			skill->SetName("Ars Arcanum");
			skill->SetActionCost(100);
			skill->SetMaxTurnCooldown(6);
			skill->SetStatusEffect(2, "Bleed");
			skill->SetStatusEffect(2, "Debuff");
			skill->SetRequiredPosition(2, true);
			for (int i = 0; i < 3; i++)
			{
				skill->SetSelectableTarget(i, true);
			}
			SkillList.push_back(skill);
		}
		else if (Level == 5)
		{
			skill->SetName("Miasmic Cloud");
			skill->SetActionCost(40);
			skill->SetMaxTurnCooldown(2);
			skill->SetStatusEffect(3, "Debuff");
			skill->SetRequiredPosition(1, true);
			skill->SetRequiredPosition(2, true);
			for (int i = 0; i < 3; i++)
			{
				skill->SetSelectableTarget(i, true);
			}
			SkillList.push_back(skill);
		}
		else if (Level == 4)
		{
			skill->SetName("Unholy Incantation");
			skill->SetActionCost(40);
			skill->SetMaxTurnCooldown(2);
			//skill->SetShiftPosition()
			skill->SetRequiredPosition(0, true);
			skill->SetRequiredPosition(1, true);
			skill->SetSelectableTarget(0, true);
			skill->SetSelectableTarget(1, true);

			SkillList.push_back(skill);
		}
		else
		{
			delete skill;
			skill = nullptr;
		}
	}

	for (vector<Skill*>::iterator it = SkillList.begin(); it != SkillList.end(); it++)
	{
		Skill* SkillItr = (*it);
		if (SkillItr->GetName() == "Ars Arcanum")
			SkillItr->SetDamage((int)(GetAttack() * 0.9));
		else if (SkillItr->GetName() == "Unholy Incantation")
			SkillItr->SetDamage((int)(GetAttack() * 0.2));
		else if (SkillItr->GetName() == "Blinding Flash")
			SkillItr->SetDamage((int)(GetAttack() * 0.15));
		else if (SkillItr->GetName() == "Magic Bolt")
			SkillItr->SetDamage((int)(GetAttack() * 0.75));
	}
}

void Mage::Update(double dt)
{
	
}