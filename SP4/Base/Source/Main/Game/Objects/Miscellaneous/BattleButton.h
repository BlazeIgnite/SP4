#pragma once

#include "../../Objects/Items/ItemEntity.h"
#include "../../Miscellaneous/Button.h"
#include "../../Miscellaneous/Description.h"

class BattleButton
{
private:
	//Characters
	Button* Character1;
	Button* Character2;
	Button* Character3;

	//Consumables
	Button* RedPotion;
	Button* BluePotion;
	Button* AttackPotion;
	Button* DefencePotion;
	Button* Bandage;

	//Skills
	Button* Skill1;
	Button* Skill2;
	Button* Skill3;

	//AI
	Button* AI1;
	Button* AI2;
	Button* AI3;

	std::vector<Button*> buttonList;

public:
	BattleButton();
	~BattleButton();

	void Init();
	void Update(float dt);


};

