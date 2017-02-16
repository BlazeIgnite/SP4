#include "Consumables.h"

Consumables::Consumables()
{
}


Consumables::~Consumables()
{
}

void Consumables::Init()
{
}

void Consumables::Update(double dt)
{

}

int Consumables::UseHealthPot(int HP)
{
	HP += 30;
	if (HP >= 100)
		HP = 100;
	return HP;
}

int Consumables::UseManaPot(int Mana)
{
	Mana += 10;
	if (Mana >= 100)
		Mana = 100;
	return Mana;
}

int Consumables::UseAtkBuffPot(int Attack)
{
	Attack += 10;
	if (Attack >= 100)
		Attack = 100;
	return Attack;
}

int Consumables::UseDefBuffPot(int Defense)
{
	Defense += 10;
	if (Defense >= 100)
		Defense = 100;
	return Defense;
}