#pragma once

#include <string>

class Consumables
{
public:
	Consumables();
	~Consumables();

	void Init();
	void Update(double dt);
	

	int UseRedPot(int HP, int Capacity);
	int UseManaPot(int Mana, int Capacity);
	//int UseBandage()
	int UseAtkBuffPot(int Attack, int Capacity);
	int UseDefBuffPot(int Defense, int Capacity);
};

