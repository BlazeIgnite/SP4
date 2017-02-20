#pragma once

#include "../Objects/Items/ItemEntity.h"
#include "../Miscellaneous/Button.h"
#include "../Miscellaneous/Description.h"

#include "../../Engine/Objects/SceneEntity.h"
#include <vector>
#include "SceneBase.h"
#include "../../Engine/Objects/BaseObject.h"

class SplashScreen : public SceneEntity
{
private:
	Button* NewGame;
	Button* LoadGame;
	Button* ExitGame;

	Camera camera;
public:
	SplashScreen();
	~SplashScreen();

	void Init();
	void Update(float dt);
	void Render();
	void Exit();
	std::vector<Button*> buttonList;

};

