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
	int UseAtkBuffPot(int Attack);
	int UseDefBuffPot(int Defense);
};

