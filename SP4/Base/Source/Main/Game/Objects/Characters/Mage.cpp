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

}

Mage::~Mage()
{

}

void Mage::Init(int Level)
{
	Name = "Mage";
	if (Level > 0 && Level < 21)
	{
		SetLevel(Level);
		SetHealth(MageHealth[Level - 1]);
		SetMaxHealth(MageHealth[Level - 1]);
		SetAbilityPoints(MageAbilityPoints[Level - 1]);
		SetMaxAbilityPoints(MageAbilityPoints[Level - 1]);
		SetAttack(MageAttack[Level - 1]);
		SetDefense(MageDefense[Level - 1]);
		SetMagic(MageMagic[Level - 1]);
		SetLuck(MageLuck[Level - 1]);
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
		SetHealth((MageHealth[19] * finalscale));
		SetMaxHealth(MageHealth[19] * finalscale);
		SetAbilityPoints(MageAbilityPoints[19] * finalscale);
		SetMaxAbilityPoints(MageAbilityPoints[19] * finalscale);
		SetAttack(MageAttack[19] * finalscale);
		SetDefense(MageDefense[19] * finalscale);
		SetMagic(MageMagic[19] * finalscale);
		SetLuck(MageLuck[19] * finalscale);
		cout << "HP: " << GetHealth() << "/" << GetMaxHealth()
			<< endl << "AP: " << GetAbilityPoints() << "/" << GetMaxAbilityPoints()
			<< endl << "Attack: " << GetAttack()
			<< endl << "Defense: " << GetDefense()
			<< endl << "Magic: " << GetMagic()
			<< endl << "Luck" << GetLuck() << endl;
	}
	SetPosition(Position_Back);
	SetDamageMitigation();



	skill_1 = new OffensiveSkill();
	skill_1->SetSkill_IDs("Magic Bolt", 1);
	skill_1->SetAbilityCost(5);
	skill_1->SetMultiplier(0.65f);
	skill_1->SetActionCost(20.f);
	skill_1->SetScaleFactor(Skill::Scale_Magic);
	skill_1->SetSkillPosition(Position_Front);
	skill_1->SetSkillTarget(Target_Front);
	skill_1->shiftposition = 0;
}

void Mage::Levelup()
{

}

void Mage::Update(double dt)
{
	
}