#pragma once

#include <string>

class Consumables
{
public:
	Consumables();
	~Consumables();

	void Init();
	void Update(double dt);

	int UseHealthPot(int HP);
	int UseManaPot(int Mana);
	//int UseBandage()
	float UseAtkBuffPot(int Attack);
	float UseDefBuffPot(int Defense);
};

