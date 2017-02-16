#include "Warrior.h"
#include <iostream>
using std::cout;
using std::endl;

float WarriorHealth[] = { 25, 25, 31, 34, 38, 38, 41, 47, 52, 59, 66, 71, 75, 81, 85, 90, 95, 103, 110, 125 };
float WarriorAbilityPoints[] = { 15, 15, 15, 20, 24, 27, 31, 32, 34, 37, 38, 39, 41, 43, 46, 50, 51, 53, 55, 60 };
float WarriorAttack[] = { 13, 15, 15, 17, 19, 19, 21, 23, 25, 30, 33, 37, 43, 48, 50, 54, 55, 60, 63, 66 };
float WarriorDefense[] = { 15, 15, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };
float WarriorMagic[] = { 2, 15, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };
float WarriorLuck[] = { 1, 15, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };

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
	if (Level > 20)
	{
		float Levelscale = Level - 20;
		float finalscale = 1 + (Levelscale * 0.01f);
		SetLevel(Level);
		SetHealth((WarriorHealth[19] * finalscale));
		SetMaxHealth(WarriorHealth[19] * finalscale);
		SetAbilityPoints(WarriorAbilityPoints[19] * finalscale);
		SetMaxAbilityPoints(WarriorAbilityPoints[19] * finalscale);
		SetAttack(WarriorAttack[19] * finalscale);
		SetDefense(WarriorDefense[19] * finalscale);
		SetMagic(WarriorMagic[19] * finalscale);
		SetLuck(WarriorLuck[19] * finalscale);
		cout << "HP: " << GetHealth() << "/" << GetMaxHealth()
			<< endl << "AP: " << GetAbilityPoints() << "/" << GetMaxAbilityPoints()
			<< endl << "Attack: " << GetAttack()
			<< endl << "Defense: " << GetDefense()
			<< endl << "Magic: " << GetMagic()
			<< endl << "Luck" << GetLuck() << endl;
	}
	SetPosition(Position_Front);
	SetDamageMitigation();
	


	//Sets up Skills used
	skill_1 = new OffensiveSkill();
	skill_1->SetCharacter(this);
	skill_1->SetSkill_IDs("Bash", 1);
	skill_1->SetAbilityCost(5);
	skill_1->SetMultiplier(0.65f);
	skill_1->SetActionCost(20.f);
	skill_1->SetScaleFactor(Skill::Scale_Attack);
	skill_1->SetSkillPosition(Position_Front);
	skill_1->SetSkillTarget(Target_Front);
	skill_1->shiftposition = 0;


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

void Warrior::Update(double dt)
{

}