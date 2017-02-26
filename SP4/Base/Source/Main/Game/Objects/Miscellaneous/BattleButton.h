#pragma once

#include "../../Objects/Items/ItemEntity.h"
#include "../../Miscellaneous/Button.h"
#include "../../Miscellaneous/Description.h"

class BattleButton
{
private:
	Button* button;
	std::vector<Button*> buttonList;

public:
	BattleButton();
	~BattleButton();

	void Init();
	void Update(float dt);
	void Render();
	void Exit();

	Vector3 tempscale;
	Vector3 tempscale1;

	std::vector<Button*>* GetList();

};

