#include "AIBase.h"


AIBase::AIBase()
{
}


AIBase::~AIBase()
{
}

void AIBase::Init()
{
	stateHolder = new AIStateManager();
	BattlePlanHolder = new AIBattlePlanner();
}

void AIBase::Exit()
{
	if (stateHolder != nullptr)
	{
		delete stateHolder;
		stateHolder = nullptr;
	}
	if (BattlePlanHolder != nullptr)
	{
		delete BattlePlanHolder;
		BattlePlanHolder = nullptr;
	}
	for (vector<CharacterEntity*>::iterator it = TroopList.begin(); it != TroopList.end(); it++)
	{
		if ((*it) != nullptr)
		{
			delete (*it);
			(*it) = nullptr;
			TroopList.pop_back();
		}
	}
}

void AIBase::AddTroop(CharacterEntity* Troop)
{
	TroopList.push_back(Troop);
}

vector<CharacterEntity*> AIBase::GetAIList()
{
	return TroopList;
}

CharacterEntity* AIBase::GetCharacterEntity(string Name)
{
	for (vector<CharacterEntity*>::iterator it = TroopList.begin(); it != TroopList.end(); it++)
	{
		if ((*it)->GetName() == Name)
		{
			return (*it);
		}
	}
	return nullptr;
}