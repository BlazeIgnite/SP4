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
#include "../Objects/Characters/CharacterEntity.h"

class SceneLevel2 : public SceneEntity
{

private: 
	Vector3 tempscale;
	Vector3 tempscale1;
	BattleButton* button;
	CharacterEntity* character;
	AIBase* AI = nullptr;
	vector<string> PlayerDamaged;
	vector<string> AIDamaged;
	double x, y;

	string damage;

	float ActionMeter;
	float textPos;
	float timer;

	void RenderObjects(BaseObject *obj);
	void tempRenderObjects();
	void UpdateCharacterLogic(double dt);
	void UpdateInternals(double dt);
	bool CheckCollision(BaseObject* o1, BaseObject* o2, std::string type = "Circle");

	bool renderDamage;

public:
	SceneLevel2();
	~SceneLevel2();

	void Init();
	void Update(float dt);
	void Render();
	void Exit();

	void HandleUserInput();

protected:

	//Physics Related
	float TimeMultiplier;
	unsigned short StoredIterator = 0;
	bool GameStage;

	Camera camera;
};
