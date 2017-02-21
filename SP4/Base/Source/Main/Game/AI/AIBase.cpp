#include "AIBase.h"


AIBase::AIBase()
{
}


AIBase::~AIBase()
{
	Exit();
}

void AIBase::Init()
{
	stateHolder = new AIStateManager();
	BattlePlanHolder = new AIBattlePlanner();
}

void AIBase::Exit()
{
	if (stateHolder)
	{
		delete stateHolder;
		stateHolder = NULL;
	}
	if (BattlePlanHolder)
	{
		delete BattlePlanHolder;
		BattlePlanHolder = NULL;
	}
	for (vector<CharacterEntity*>::iterator it = TroopList.begin(); it != TroopList.end(); it++)
	{
		if ((*it) != NULL)
		{
			delete (*it);
			(*it) = NULL;
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