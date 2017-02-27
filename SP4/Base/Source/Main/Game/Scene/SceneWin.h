#pragma once
#include <vector>
#include "SceneBase.h"
#include "../../Engine/Objects/SceneEntity.h"
#include "../Objects/Miscellaneous/BattleButton.h"

class SceneWin :public SceneEntity
{
public:
	SceneWin();
	~SceneWin();

	virtual void Init();
	virtual void Update(float dt);
	virtual void Render();
	virtual void Exit();


protected:
	int NumCharacters = 0;

	//Physics Related
	float TimeMultiplier;
	unsigned short StoredIterator = 0;
	bool GameStage;

	Camera camera;
};