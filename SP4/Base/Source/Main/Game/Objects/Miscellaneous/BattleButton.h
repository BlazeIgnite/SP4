#pragma once

#include "../../Objects/Items/ItemEntity.h"
#include "../../Miscellaneous/Button.h"
#include "../../Miscellaneous/Description.h"

class BattleButton
{
private:
	Button* button;
	std::vector<Button*> buttonList;
	std::vector<Description*> descripList;

public:
	BattleButton();
	~BattleButton();

	void Init(double x, double y);
	void Update(float dt);
	void UpdateDescription(float dt);
	void Render();
	void Exit();

	std::vector<Button*>* GetList();
	std::vector<Description*>* GetDescriList();
};

