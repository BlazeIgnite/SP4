#pragma once
#include <vector>

#include "SceneBase.h"
#include "../../Engine/Objects/SceneEntity.h"
#include "../Miscellaneous/Button.h"

using std::vector;

class SceneLevelSelection : public SceneEntity
{
private:
	vector<Button*> m_buttonList;

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