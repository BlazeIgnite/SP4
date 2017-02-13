#ifndef SCENE_ASSIGNMENT1_H
#define SCENE_ASSIGNMENT1_H

#include "../../Engine/Objects/BaseObject.h"
#include <vector>
#include "SceneBase.h"

class Scene_Assignment1 : public SceneBase
{
private:
	void RenderObjects(BaseObject *obj);
	void UpdateCharacterLogic(double dt);
	void UpdateInternals(double dt);
	bool CheckCollision(BaseObject* o1, BaseObject* o2, std::string type = "Circle");

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