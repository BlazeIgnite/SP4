#include "Mage.h"
#include <iostream>
using std::cout;
using std::endl;

size_t MageHealth[] = { 0, 15, 100, 20, 24, 28, 30, 31, 33, 35, 37, 42, 47, 55, 60, 65, 71, 80, 81, 82, 85 };
size_t MageAttack[] = { 0, 15, 17, 19, 21, 25, 29, 34, 37, 40, 44, 50, 56, 64, 66, 70, 75, 80, 83, 84, 89 }; 
float MageDefence[] = { 0.f, 1.0f, 1.4f, 1.8f, 2.2f, 2.6f, 3.0f, 4.f, 4.4f, 4.8f, 5.2f, 5.6f, 6.0f, 7.0f, 7.6f, 8.2f, 8.8f, 9.4f, 10.f, 10.f, 10.f };
size_t ExperienceNeed[] = {0, 0, 10, 30, 55, 70, 100, 130, 165, 200, 240, 285, 325, 370, 420, 475, 530, 590, 650, 720};


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
	SetisPressed(false);
	SetisSelected(false);
	for (int i = 0; i < Level; i++)
	{
		LevelUp(true);
	}

}

void Mage::LevelUp(bool init)
{
	if (init)
		Level++;
	else
	{
		if (ExperiencePoints > ExperienceNeed[Level + 1])
			Level++;
		else
			return;
	}

	ExperiencePoints = (float)ExperienceNeed[Level];
	SetHealth(MageHealth[Level]);
	SetMaxHealth(MageHealth[Level]);
	SetAttack(MageAttack[Level]);
	SetDefence((size_t)MageDefence[Level]);
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
			skill->SetRequiredPosition(1, true);
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
			skill->SetRequiredPosition(1, true);
			skill->SetRequiredPosition(2, true);
			skill->SetSelectableTarget(2, true);
			skill->SetStatusEffect(1, "Debuff");
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
			skill->SetRequiredPosition(1, true);
			skill->SetRequiredPosition(2, true);
			for (size_t i = 0; i < 3; i++)
			{
				skill->SetSelectableTarget(i, true);
			}
			SkillList.push_back(skill);

			skill = new Skill();
			skill->SetName("Blinding Flash");
			skill->SetActionCost(35);
			skill->SetStatusEffect(1, "Stun");
			skill->SetMaxTurnCooldown(1);
			for (size_t i = 0; i < 3; i++)
			{
				skill->SetRequiredPosition(i, true);
				skill->SetSelectableTarget(i, true);
			}
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
			SkillItr->SetDamage((int)(Attack * 1.4));
		else if (SkillItr->GetName() == "Unholy Incantation")
			SkillItr->SetDamage((int)(Attack * 0.2));
		else if (SkillItr->GetName() == "Blinding Flash")
			SkillItr->SetDamage((int)(Attack * 0.15));
		else if (SkillItr->GetName() == "Magic Bolt")
			SkillItr->SetDamage((int)(Attack * 0.75));
		else if (SkillItr->GetName() == "Basic Attack")
			SkillItr->SetDamage((int)(Attack * 0.5));

	}
}

void Mage::Update(double dt)
{
	
}