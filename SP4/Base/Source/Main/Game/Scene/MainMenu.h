#ifndef MAINMENU_H
#define MAINMENU_H

#include "../Objects/Items/ItemEntity.h"
#include "../Miscellaneous/Button.h"
#include "../Miscellaneous/Description.h"
#include "../Objects/Characters/Player.h"

#include "../../Engine/Objects/SceneEntity.h"
#include <vector>
#include "SceneBase.h"
#include "../../Engine/Objects/BaseObject.h"

class MainMenu : public SceneEntity
{
private:
	Button* Start;
	Button* Setting;
	Button* ExitGame;

	Camera camera;

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