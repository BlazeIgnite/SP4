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
	HP += 50;
	return HP;
}

int Consumables::UseManaPot(int Mana)
{
	Mana += 10;
	return Mana;
}

float Consumables::UseAtkBuffPot(int Attack)
{
	Attack = (int)(Attack * 1.25f);
	return (float)Attack;
}

float Consumables::UseDefBuffPot(int Defence)
{
	Defence = (int)(Defence * 1.25f);
	return (float)Defence;
}