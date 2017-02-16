#ifndef SCENE_ASSIGNMENT1_H
#define SCENE_ASSIGNMENT1_H

#include "../../Engine/Objects/BaseObject.h"
#include <vector>
#include "SceneBase.h"
#include "../Miscellaneous/Button.h"
#include "../Miscellaneous/Description.h"
#include "../Objects/Characters/Warrior.h"
#include "../AI/AIBehaviors/AIDefault.h"
#include "../Objects/Characters/Player.h"
#include "../Systems/BattleSystem.h"

class Button;
class Description;
class Warrior;

class Scene_Assignment1 : public SceneBase
{
private:
	void RenderObjects(BaseObject *obj);
	void tempRenderObjects();
	void UpdateCharacterLogic(double dt);
	void UpdateInternals(double dt);
	bool CheckCollision(BaseObject* o1, BaseObject* o2, std::string type = "Circle");
	Button* button;
	Button* button2;
	Player* player;
	AIBase* AI;
	//BattleSystem* bs;
	//Warrior* warrior1;
	//Warrior* warrior2;
	Description* display;

	std::vector<Button*> buttonVector;
	std::vector<Description*> DescriptionVector;

	double x, y;

public:
	Scene_Assignment1();
	~Scene_Assignment1();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	void HandleUserInput();

protected:
	int NumCharacters = 0;

	//Physics Related
	float TimeMultiplier;
	unsigned short StoredIterator = 0;


};

#endif