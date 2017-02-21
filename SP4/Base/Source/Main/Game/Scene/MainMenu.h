#ifndef MAINMENU_H
#define MAINMENU_H

#include "../Objects/Items/ItemEntity.h"
#include "../Miscellaneous/Button.h"
#include "../Miscellaneous/Description.h"

#include "../../Engine/Objects/SceneEntity.h"
#include <vector>
#include "SceneBase.h"
#include "../../Engine/Objects/BaseObject.h"

class MainMenu : public SceneEntity
{
private:
	//Button* StartMission;
	//Button* Inventory;
	//Button* ExitGame;
	Button* button;
	Camera camera;

	double x, y;

public:
	MainMenu();
	~MainMenu();

	void Init();
	void Update(float dt);
	void Render();
	void Exit();

	std::vector<Button*> buttonList;
};

#endif