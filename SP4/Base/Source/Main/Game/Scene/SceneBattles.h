#pragma once
#include <vector>
#include "SceneBase.h"
#include "../Objects/Characters/Warrior.h"
#include "../AI/AIBehaviors/AIAllAttack.h"
#include "../AI/AIBehaviors/AIStatusEffect.h"
#include "../Systems/BattleSystem.h"
#include "../../Engine/Objects/BaseObject.h"
#include "../../Engine/Objects/SceneEntity.h"
#include "../Objects/Miscellaneous/BattleButton.h"


class SceneBattles : public SceneEntity
{

private:
	void RenderObjects(BaseObject *obj);
	void tempRenderObjects();
	void UpdateCharacterLogic(double dt);
	void UpdateInternals(double dt);
	bool CheckCollision(BaseObject* o1, BaseObject* o2, std::string type = "Circle");

	double x, y;

	BattleButton* button;

	AIBase* AI = nullptr;

public:
	SceneBattles();
	~SceneBattles();

	virtual void Init();
	virtual void Update(float dt);
	virtual void Render();
	virtual void Exit();

	void HandleUserInput();
protected:

	//Physics Related
	float TimeMultiplier;
	unsigned short StoredIterator = 0;
	bool GameStage;

	Camera camera;
};

