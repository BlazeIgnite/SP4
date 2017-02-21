#include "Mage.h"
#include <iostream>
using std::cout;
using std::endl;

size_t MageHealth[] = { 0, 15, 17, 20, 24, 28, 30, 31, 33, 35, 37, 42, 47, 55, 60, 65, 71, 80, 81, 82, 85 };
size_t MageAttack[] = { 0, 15, 17, 19, 21, 25, 29, 34, 37, 40, 44, 50, 56, 64, 66, 70, 75, 80, 83, 84, 89 }; 
float MageDefense[] = { 0.f, 1.0f, 1.4f, 1.8f, 2.2f, 2.6f, 3.0f, 4.f, 4.4f, 4.8f, 5.2f, 5.6f, 6.0f, 7.0f, 7.6f, 8.2f, 8.8f, 9.4f, 10.f, 10.f, 10.f };


Mage::Mage()
{
	NormalAttackmultiplier = 0.50f;
	Name = "Mage";
}

Mage::~Mage()
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

void Mage::Init(int Level)
{
	for (int i = 0; i < Level; i++)
	{
		LevelUp();
	}

}

void Mage::LevelUp()
{
	Level++;

	SetHealth(MageHealth[Level]);
	SetAttack(MageAttack[Level]);
	SetDefense(MageDefense[Level]);
	SetDamageMitigation();
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
		else if (Level == 1)
		{
			skill->SetName("Basic Attack");
			skill->SetActionCost(20);
			for (size_t i = 0; i < 3; i++)
			{
				skill->SetRequiredPosition(i, true);
			}
			skill->SetSelectableTarget(0, true);
			skill->SetSelectableTarget(1, true);
			SkillList.push_back(skill);

			// Magic Bolt
			skill = new Skill();
			skill->SetName("Magic Bolt");
			skill->SetActionCost(30);
			skill->SetMaxTurnCooldown(1);
			skill->SetRequiredPosition(0, 1);
			SkillList.push_back(skill);

			skill = new Skill();
			skill->SetName("Blinding Flash");
			skill->SetActionCost(35);
			skill->SetMaxTurnCooldown(1);
			skill->SetRequiredPosition(0, true);
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
			SkillItr->SetDamage((int)(DamageMitigation * 0.9));
		else if (SkillItr->GetName() == "Unholy Incantation")
			SkillItr->SetDamage((int)(DamageMitigation * 0.2));
		else if (SkillItr->GetName() == "Blinding Flash")
			SkillItr->SetDamage((int)(DamageMitigation * 0.15));
		else if (SkillItr->GetName() == "Magic Bolt")
			SkillItr->SetDamage((int)(GetAttack() * 0.75));
		else if (SkillItr->GetName() == "Basic Attack")
			SkillItr->SetDamage((int)(DamageMitigation * 0.5));

	}
}

void Mage::Update(double dt)
{
	
}