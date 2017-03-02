#ifndef SCENE_LEVEL_3
#define SCENE_LEVEL_3
#include <vector>
#include "SceneBase.h"
#include "../Objects/Characters/Warrior.h"
#include "../AI/AIBehaviors/AIAllAttack.h"
#include "../Systems/BattleSystem.h"
#include "../../Engine/Objects/BaseObject.h"
#include "../../Engine/Objects/SceneEntity.h"
#include "../Objects/Miscellaneous/BattleButton.h"
#include "../Objects/Characters/CharacterEntity.h"


class SceneLevel3 : public SceneEntity
{

private:
	Vector3 tempscale;
	Vector3 tempscale1;
	BattleButton* button;
	AIBase* AI = nullptr;
	double x, y;

	size_t i;
	string damage;

	float ActionMeter;
	float textPosY;
	float startPosY;
	float timer;

	void RenderObjects(BaseObject *obj);
	void tempRenderObjects();
	void UpdateCharacterLogic(double dt);
	void UpdateInternals(double dt);
	bool CheckCollision(BaseObject* o1, BaseObject* o2, std::string type = "Circle");

	bool renderDamage;
public:
	SceneLevel3();
	~SceneLevel3();

	virtual void Init();
	virtual void Update(float dt);
	virtual void Render();
	virtual void Exit();
protected:

	//Physics Related
	float TimeMultiplier;
	unsigned short StoredIterator = 0;
	bool GameStage;
	void SpawnWave(int Wave);
	int Waves;
	int Currentwave;
	bool Wavecleared = false;
	Camera camera;
};

#endif