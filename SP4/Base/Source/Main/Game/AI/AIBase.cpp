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
}

void AIBase::Exit()
{
	if (stateHolder)
	{
		delete stateHolder;
		stateHolder = NULL;
	}
}

void AIBase::AddTroop(string Name, CharacterEntity* Troop)
{
	std::map<string, std::vector<CharacterEntity*>>::iterator itr = TroopList.find(Name);
	if (itr == TroopList.end())
	{
		std::vector < CharacterEntity* > emptyCharacterEntity;
		emptyCharacterEntity.push_back(Troop);
		TroopList[Name] = emptyCharacterEntity;
		//UnitList[Name].push_back(newCharacter);
		//UnitList.insert(std::pair <string, std::vector<CharacterEntity*>>(Name, newCharacter));
	}
	else
	TroopList.find(Name)->second.push_back(Troop);
}

map<string, vector<CharacterEntity*>> AIBase::GetAllAIList()
{
	return TroopList;
}

vector<CharacterEntity*> AIBase::GetClassAIList(string& Name)
{
	return TroopList.find(Name)->second;
}
vector<CharacterEntity*> AIBase::GetClassAIList(string Name)
{
	return TroopList.find(Name)->second;
}