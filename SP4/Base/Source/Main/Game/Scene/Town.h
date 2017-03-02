#pragma once

#include "../Objects/Items/ItemEntity.h"
#include "../Miscellaneous/Button.h"
#include "../Miscellaneous/Description.h"
#include "../Objects/Miscellaneous/InventoryButtons.h"

#include "../../Engine/Objects/SceneEntity.h"
#include <vector>
#include "SceneBase.h"
#include "../../Engine/Objects/BaseObject.h"

class Town : public SceneEntity
{
private:
	Button* button;
	InventoryButtons* inventory;
	double x, y;
	bool OpenInventory;
	bool OpenCraftingTab;
	bool isSelected;
	bool OpenSetting;
	bool OpenMission;
	Camera camera;
	float Volume;

public: 
	Town();
	~Town();

	void Init();
	void Update(float dt);
	void UpdateInventory(float dt);
	void Render();
	void RenderInventoryButtons();
	void RenderCraftingButtons();
	void RenderSetting();
	void Exit();

	std::vector<Button*> buttonList;
};

