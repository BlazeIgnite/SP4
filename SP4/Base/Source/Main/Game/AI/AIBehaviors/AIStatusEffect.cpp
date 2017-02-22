#include "AIStatusEffect.h"
#include "../../Systems/BattleSystem.h"


AIStatusEffect::AIStatusEffect()
{
	Init();
}

AIStatusEffect::~AIStatusEffect()
{
}

void AIStatusEffect::Init()
{
	for (size_t i = 0; i < BattleSystem::Instance().GetPlayerTroops().size(); i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			SetPlayerTroopStatusE(BattleSystem::Instance().GetPlayerTroops().find(i)->first, j, false);
		}
	}
} 

void AIStatusEffect::Update(double dt)
{
	if (!BattleSystem::Instance().GetPlayerTurn())
	{
		if (stateHolder->GetState(""))
			stateHolder->SetState("Planning");
		else if (stateHolder->GetState("Planning"))
			Planning();
		else if (stateHolder->GetState("Execute"))
			Execute();
	}
}

void AIStatusEffect::Planning()
{
	
}

void AIStatusEffect::Execute()
{}

void AIStatusEffect::Exit()
{
	AIBase::Exit();
}

void AIStatusEffect::SetPlayerTroopStatusE(size_t troopPosition, size_t statusID, bool newStatusE)
{
	map<size_t, map<size_t, bool>>::iterator it = m_PlayerTroopStatusE.find(troopPosition);
	if (it == m_PlayerTroopStatusE.end())
	{
		map<size_t, bool> EmptyMap;
		EmptyMap[statusID] = newStatusE;
		m_PlayerTroopStatusE[troopPosition] = EmptyMap;
	}
	else
	{
		map<size_t, bool>::iterator it2 = it->second.find(statusID);
		if (it2 == it->second.end())
			m_PlayerTroopStatusE.find(troopPosition)->second[statusID] = newStatusE;
		else
			m_PlayerTroopStatusE.find(troopPosition)->second.at(statusID) = newStatusE;
	}
}

bool AIStatusEffect::GetPlayerTroopStatusE(size_t troopPosition, size_t statusID)
{
	return m_PlayerTroopStatusE.find(troopPosition)->second.find(statusID)->second;
}