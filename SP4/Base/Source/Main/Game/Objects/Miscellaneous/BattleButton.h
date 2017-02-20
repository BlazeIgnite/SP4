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

	std::vector<Button*>* GetList();

};

