#include "Priest.h"
#include <iostream>
using std::cout;
using std::endl;

float PriestHealth[] = { 25, 25, 31, 34, 38, 38, 41, 47, 52, 59, 66, 71, 75, 81, 85, 90, 95, 103, 110, 125 };
float PriestAbilityPoints[] = { 15, 15, 15, 20, 24, 27, 31, 32, 34, 37, 38, 39, 41, 43, 46, 50, 51, 53, 55, 60 };
float PriestAttack[] = { 13, 15, 15, 17, 19, 19, 21, 23, 25, 30, 33, 37, 43, 48, 50, 54, 55, 60, 63, 66 };
float PriestDefense[] = { 15, 15, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };
float PriestMagic[] = { 2, 15, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };
float PriestLuck[] = { 1, 15, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };


Priest::Priest()
{
	NormalAttackmultiplier = 0.40f;
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

void Priest::Levelup()
{

}

void Priest::Update(double dt)
{

}