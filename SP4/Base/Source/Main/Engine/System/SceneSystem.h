/*
Copyright (c) Lim Rui An, Ryan 2016

Creator(s)    : Lim Rui An, Ryan
Creation Date : 30 September 2016 10:42 AM
File Name     : SceneSystem.h
Purpose       : Defines a SceneSystem
*/

#ifndef SCENE_SYSTEM_H
#define SCENE_SYSTEM_H

#include "../Internal/System.h"
#include "../Internal/SingletonTemplate.h"
#include "../Objects/SceneEntity.h"
#include "../../Base/Source/Main/Game/Scene/SceneBase.h"
#include <map>
#include <queue>
#include "Utility.h"
#include "InputManager.h"

class SceneSystem : public System, public SingletonTemplate<SceneSystem>
{
public:
	virtual void Init();
	virtual void Update(const float& dt);
	virtual void Render(void){};
	//virtual void SendMessage(const string&){};
	virtual void Exit(void){};

	virtual void AddScene(SceneBase&);

	virtual void SwitchScene(const std::string&);
	virtual bool SwitchToPreviousScene();

	SceneBase &GetCurrentScene();
	//SceneBase &GetRenderSystem();

	virtual void SetRenderSystem(SceneBase&);
	virtual void ClearMemoryUsage();

	InputManager* cSS_InputManager;

protected:
	int MaxStoredHistory;
	std::queue<SceneBase*> SceneHistory;
	std::map<std::string, SceneBase*> StoredSceneList;
	SceneEntity *Renderer;

};

#endif