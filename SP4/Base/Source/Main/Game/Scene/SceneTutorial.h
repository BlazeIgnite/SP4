#pragma once
#include <vector>
#include "SceneBase.h"
#include "../Objects/Characters/Warrior.h"
#include "../AI/AIBehaviors/AITutorial.h"
#include "../Systems/BattleSystem.h"
#include "../../Engine/Objects/BaseObject.h"
#include "../../Engine/Objects/SceneEntity.h"
#include "../Objects/Miscellaneous/BattleButton.h"
#include "../Objects/Characters/CharacterEntity.h"


class SceneTutorial : public SceneEntity
{

private:
	Vector3 tempscale;
	Vector3 tempscale1;

	BattleButton* m_button;
	AIBase* m_AI = nullptr;

	double x, y;

	size_t m_Turn;
	size_t i;
	size_t m_attackTimes;
	string m_damage;

	float m_ActionMeter;
	float m_textPosY;
	float m_startPosY;
	float m_timer;

	void RenderObjects(BaseObject *obj);
	void tempRenderObjects();
	void UpdateCharacterLogic(double dt);
	void UpdateInternals(double dt);
	bool CheckCollision(BaseObject* o1, BaseObject* o2, std::string type = "Circle");

	bool m_renderDamage;

	bool m_T1pressAttack;
	bool m_T2pressHeal;

public:
	SceneTutorial();
	~SceneTutorial();

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

