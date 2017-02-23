#ifndef MAINMENU_H
#define MAINMENU_H

#include "../Objects/Items/ItemEntity.h"
#include "../Miscellaneous/Button.h"
#include "../Miscellaneous/Description.h"
#include "../Objects/Miscellaneous/InventoryButtons.h"

#include "../../Engine/Objects/SceneEntity.h"
#include <vector>
#include "SceneBase.h"
#include "../../Engine/Objects/BaseObject.h"

class MainMenu : public SceneEntity
{
private:
	Button* button;
	Camera camera;

	bool OpenInventory;
	bool isPressed;

	double x, y;
	InventoryButtons* inventory;
	std::string NewName;
public:
	MainMenu();
	~MainMenu();

	void Init();
	void Update(float dt);
	void Render();
	void Exit();

	void InitButtons();
	void RenderButtons();
	void RenderNameInput();

	std::vector<Button*> buttonList;

	bool LoadFile;
	bool NewGame;
	bool NameInput;
};

#endif