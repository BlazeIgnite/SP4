#ifndef SCENE_ASSIGNMENT1_H
#define SCENE_ASSIGNMENT1_H

#include "../../Engine/Objects/BaseObject.h"
#include "../../Engine/Objects/SceneEntity.h"
#include <vector>
#include "SceneBase.h"
#include "../Objects/Characters/Warrior.h"
#include "../AI/AIBehaviors/AIDefault.h"
#include "../Objects/Characters/Player.h"
#include "../Systems/BattleSystem.h"
#include "../Objects/Miscellaneous/InventoryButtons.h"

class Scene_Assignment1 : public SceneEntity
{
private:
	void RenderObjects(BaseObject *obj);
	void tempRenderObjects();
	void UpdateCharacterLogic(double dt);
	void UpdateInternals(double dt);
	bool CheckCollision(BaseObject* o1, BaseObject* o2, std::string type = "Circle");
	
	AIBase* AI;
	//BattleSystem* bs;
	//Warrior* warrior1;
	//Warrior* warrior2;
	InventoryButtons* inventory;
	double x, y;

public:
	Scene_Assignment1();
	~Scene_Assignment1();

	virtual void Init();
	virtual void Update(float dt);
	virtual void Render();
	virtual void Exit();

	void HandleUserInput();
	void RenderCraftingButtons();
protected:
	int NumCharacters = 0;

	//Physics Related
	float TimeMultiplier;
	unsigned short StoredIterator = 0;
	bool GameStage;

	Camera camera;
};

#endif