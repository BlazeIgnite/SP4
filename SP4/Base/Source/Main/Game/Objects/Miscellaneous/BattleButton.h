#pragma once

#include "../../Objects/Items/ItemEntity.h"
#include "../../Miscellaneous/Button.h"
#include "../../Miscellaneous/Description.h"

class BattleButton
{
private:

	std::vector<Button*> buttonList;

public:
	BattleButton();
	~BattleButton();

	void Init();
	void Update(float dt);
	void Render();
	void Exit();

	Vector3 tempscale;

	std::vector<Button*>* GetList();

};

