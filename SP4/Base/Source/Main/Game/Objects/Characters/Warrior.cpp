#include "Warrior.h"
#include "Skill.h"

size_t WarriorHealth[] = { 0, 25, 29, 35, 36, 38, 38, 41, 47, 52, 59, 66, 71, 75, 81, 85, 90, 95, 103, 110, 125 };
size_t WarriorAttack[] = { 0, 7, 7, 7, 8, 9, 19, 21, 23, 25, 30, 33, 37, 43, 48, 50, 54, 55, 60, 63, 66 };
size_t ExperienceWNeed[] = { 0, 0, 10, 30, 55, 70, 100, 130, 165, 200, 240, 285, 325, 370, 420, 475, 530, 590, 650, 720 };
float WarriorDefence[] = { 0.f, 3.0f, 3.8f, 4.6f, 5.4f, 6.2f, 7.0f, 7.8f, 8.6f, 9.4f, 10.2f, 11.0f, 11.9f, 12.8f, 13.7f, 14.6f, 15.5f, 17.f, 18.5f, 20.f, 25.f };

Warrior::Warrior()
{
	NormalAttackmultiplier = 0.75f;
	Name = "Warrior";
}

Warrior::~Warrior()
{
}

void Warrior::Init(int Level)
{
	SetisPressed(false);
	SetisSelected(false);
	//if (Level > 0 && Level < 21)
	//{
	//	SetLevel(Level);
	//	SetHealth(WarriorHealth[Level]);
	//	SetAttack(WarriorAttack[Level]);
	//	SetDefence(WarriorDefence[Level]);
	//	SetDamageMitigation();
	//}
	//
	////This Section is so that AI levels that Exceed Level 20 will be Scaled;
	//if (Level > 20)
	//{
	//	SetLevel(Level);
	//	float LevelOffset = (Level - 20) / 100;
	//	SetHealth(WarriorHealth[20] * (1 + LevelOffset));
	//	SetAttack(WarriorAttack[20] * (1 + LevelOffset));
	//	SetDefence(WarriorDefence[20] * (1 + LevelOffset));
	//	SetDamageMitigation();
	//}
	for (int i = 0; i < Level; i++)
	{
		LevelUp(true);
	}
}
void Warrior::Update(double dt)
{
	
}

void Warrior::LevelUp(bool init)
{
	if (init)
		Level++;
	else
	{
		if (ExperiencePoints > ExperienceWNeed[Level + 1])
			Level++;
		else
			return;
	}

	ExperiencePoints = (float)ExperienceWNeed[Level];
	SetHealth(WarriorHealth[Level]);
	SetMaxHealth(WarriorHealth[Level]);
	SetAttack(WarriorAttack[Level]);
	SetDefence((size_t)WarriorDefence[Level]);
	SetDamageMitigation();
	if (Level <= 10)
	{
		Skill* skill = new Skill();
		if (Level == 10)
		{
			// Divine Execution
			// Setting Name of skill
			skill->SetName("Divine Execution");

			// Setting Action Cost for Battle
			skill->SetActionCost(85);
			
			// Setting the cooldown time after activation
			skill->SetMaxTurnCooldown(5);

			// Setting the Required Position to use skill
			skill->SetRequiredPosition(0, true);

			// Setting the Selectable Position to use skill on
			skill->SetSelectableTarget(0, true);

			// Now the Warrior is allowed to use this skill
			SkillList.push_back(skill);
		}
		else if (Level == 5)
		{
			
			skill->SetName("Quick Blitz");

			// Setting Action Cost for Battle
			skill->SetActionCost(10);

			// Setting the cooldown time after activation
			skill->SetMaxTurnCooldown(1);

			// Setting the Required Position to use skill
			skill->SetRequiredPosition(0, true);
			skill->SetRequiredPosition(1, true);
			skill->SetRequiredPosition(2, true);

			// Setting the Selectable Position to use skill on
			skill->SetSelectableTarget(0, true);
			skill->SetSelectableTarget(1, true);

			// Now the Warrior is allowed to use this skill
			SkillList.push_back(skill);

		}
		else if (Level == 4)
		{

			// Stab Skill

			// Setting Name of skill
			skill->SetName("Stab");

			// Setting Action Cost for Battle
			skill->SetActionCost(25);
			
			// Setting the cooldown time after activation
			skill->SetMaxTurnCooldown(3);

			// Setting of how many turns status effect affects, what status effect is it
			skill->SetStatusEffect(3, "Bleed");

			// Setting the Required Position to use skill on
			skill->SetRequiredPosition(0, true);

			// Setting the Selectable Position to use skill on
			skill->SetSelectableTarget(0, true);
			skill->SetSelectableTarget(1, true);

			// Now the Warrior is allowed to use this skill
			SkillList.push_back(skill);
		}
		else if (Level == 2)
		{
			// Bash Skill
			// Setting Name of skill
			skill->SetName("Bash");

			// Setting Action Cost for Battle
			skill->SetActionCost(25);

			// Setting the cooldown time after activation
			skill->SetMaxTurnCooldown(2);

			// Setting of how many turns status effect affects, what status effect is it
			skill->SetStatusEffect(1, "Stun");

			// Setting the Required Position to use skill on
			skill->SetRequiredPosition(0, true);

			// Setting the Selectable Position to use skill on
			skill->SetSelectableTarget(0, true);
			skill->SetSelectableTarget(1, true);

			// Now the Warrior is allowed to use this skill
			SkillList.push_back(skill);
		}
		else if (Level == 1)
		{
			// Basic Attack
			skill->SetName("Basic Attack");

			skill->SetActionCost(25);

			for (size_t i = 0; i < 2; i++)
			{
				skill->SetRequiredPosition(i, true);
				skill->SetSelectableTarget(i, true);
			}

			SkillList.push_back(skill);


			skill = new Skill();
			skill->SetName("Rush");

			skill->SetActionCost(25);

			skill->SetShiftPosition(1);

			skill->SetMaxTurnCooldown(2);

			skill->SetStatusEffect(1, "Bleed");

			for (int i = 0; i < 3; i++)
			{
				skill->SetRequiredPosition(i, true);
			}
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

	// Updates the damage for battle system to use every time Entity levels up
	for (vector<Skill*>::iterator it = SkillList.begin(); it != SkillList.end(); it++)
	{
		Skill* SkillItr = (*it);
		if (SkillItr->GetName() == "Rush")
			SkillItr->SetDamage((int)(Attack * 0.25));
		else if (SkillItr->GetName() == "Quick Blitz")
			SkillItr->SetDamage((int)(Attack*0.5));
		else if (SkillItr->GetName() == "Bash")
			SkillItr->SetDamage((int)(Attack * 0.3));
		else if (SkillItr->GetName() == "Divine Execution")
			SkillItr->SetDamage((int)(Attack * 1.5));
		else if (SkillItr->GetName() == "Basic Attack")
			SkillItr->SetDamage((int)(Attack * 0.75));
	}
}