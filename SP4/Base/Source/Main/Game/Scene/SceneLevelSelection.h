#pragma once
#include <vector>

#include "SceneBase.h"
#include "../../Engine/Objects/SceneEntity.h"

class SceneLevelSelection : public SceneEntity
{
public:
	SceneLevelSelection();
	~SceneLevelSelection();

	virtual void Init();
	virtual void Update(float dt);
	virtual void Render();
	virtual void Exit();

protected:

	Camera camera;
};