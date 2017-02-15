#include "Warrior.h"
#include <iostream>
using std::cout;
using std::endl;

float WarriorHealth[] = { 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };
float WarriorAbilityPoints[] = { 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };
float WarriorAttack[] = { 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };
float WarriorDefense[] = { 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };
float WarriorMagic[] = { 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };
float WarriorLuck[] = { 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };

Warrior::Warrior()
{

}

Warrior::~Warrior()
{

}

void Warrior::Init(int Level)
{
	if (Level > 0 && Level < 21)
	{
		SetLevel(Level);
		SetHealth(WarriorHealth[Level - 1]);
		SetMaxHealth(WarriorHealth[Level - 1]);
		SetAbilityPoints(WarriorAbilityPoints[Level - 1]);
		SetMaxAbilityPoints(WarriorAbilityPoints[Level - 1]);
		SetAttack(WarriorAttack[Level - 1]);
		SetDefense(WarriorDefense[Level - 1]);
		SetMagic(WarriorMagic[Level - 1]);
		SetLuck(WarriorLuck[Level - 1]);
		cout << "HP: " << GetHealth() << "/" << GetMaxHealth()
			<< endl << "AP: " << GetAbilityPoints() << "/" << GetMaxAbilityPoints()
			<< endl << "Attack: " << GetAttack()
			<< endl << "Defense: " << GetDefense()
			<< endl << "Magic: " << GetMagic()
			<< endl << "Luck" << GetLuck() << endl;
	}
	


	//Sets up Skills used
	skill_1 = new OffensiveSkill();
	skill_1->SetCharacter(this);
	skill_1->SetSkill_IDs("Bash", 1);
	skill_1->SetAbilityCost(5);
	skill_1->SetMultiplier(0.65f);
	skill_1->SetActionCost(20.f);
	skill_1->SetSkillPosition(Position_Front);
	skill_1->SetSkillTarget(Target_Front);


}

void Warrior::Levelup()
{
	int TempLevel = this->GetLevel();
	TempLevel += 1;
	SetLevel(TempLevel);
	SetHealth(WarriorHealth[TempLevel - 1]);
	SetMaxHealth(WarriorHealth[TempLevel - 1]);
	SetAbilityPoints(WarriorAbilityPoints[TempLevel - 1]);
	SetMaxAbilityPoints(WarriorAbilityPoints[TempLevel - 1]);
	SetAttack(WarriorAttack[TempLevel - 1]);
	SetDefense(WarriorDefense[TempLevel - 1]);
	SetMagic(WarriorMagic[TempLevel - 1]);
	SetLuck(WarriorLuck[TempLevel - 1]);
}