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

int Consumables::UseRedPot(int HP, int Capacity ){
	if (Capacity > 0)
	{
		HP += 30;
		if (HP >= 100)
			HP = 100;
	}
	return HP;
}

int Consumables::UseManaPot(int Mana, int Capacity)
{
	if (Capacity > 0)
	{
		Mana += 10;
		if (Mana >= 100)
			Mana = 100;
	}
	return Mana;
}

int Consumables::UseAtkBuffPot(int Attack, int Capacity)
{
	if (Capacity > 0)
	{
		Attack += 10;
		if (Attack >= 100)
			Attack = 100;
	}
	return Attack;
}

int Consumables::UseDefBuffPot(int Defense, int Capacity)
{
	if (Capacity > 0)
	{
		Defense += 10;
		if (Defense >= 100)
			Defense = 100;
	}
	return Defense;
}