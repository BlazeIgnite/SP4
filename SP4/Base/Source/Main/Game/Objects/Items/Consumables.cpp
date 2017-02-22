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
	return HP;
}

int Consumables::UseManaPot(int Mana)
{
	Mana += 10;
	return Mana;
}

float Consumables::UseAtkBuffPot(int Attack)
{
	Attack *= 1.25f;
	return Attack;
}

float Consumables::UseDefBuffPot(int Defence)
{
	Defence *= 1.25f;
	return Defence;
}