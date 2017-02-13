/*
Copyright (c) Lim Rui An, Ryan 2016

Creator(s)    : Lim Rui An, Ryan
Creation Date : 26 November 2016 18:52 PM
File Name     : ObjectManager.h
Purpose       : Defines the object manager
*/

#ifndef EVENT_SYSTEM_H
#define EVENT_SYSTEM_H

#include "../../Engine/Internal/System.h"
#include "../../Engine/Internal/SingletonTemplate.h"
#include  "ObjectManager.h"
#include "Vector3.h"
#include <map>
#include <vector>

class EventSystem : public System, public SingletonTemplate<EventSystem>
{
public:
	virtual void Init();
	virtual void Update(const float& dt);
	virtual void Render(){}; 
	//virtual void SendMessage(const string&){};
	virtual void Exit(){};

	std::map<std::string, int> CurrentCharacterCount;
	void ClearCharacterCount();

private:
	void SpawnCharacter(std::string);

	std::map<std::string, int> CharacterCountLimit;
	std::map<std::string, float> SpawnTime;
	std::map<std::string, float> CollectiveTimers;
};

#endif // EVENT_SYSTEM_H