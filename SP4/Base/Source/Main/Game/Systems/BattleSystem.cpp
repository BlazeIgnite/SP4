#include "BattleSystem.h"
#include <iostream>

using std::cout;
using std::endl;

BattleSystem::BattleSystem()
{
}


BattleSystem::~BattleSystem()
{
}

void BattleSystem::Init()
{
	SetPlayerTurn(true);
	TurnCost = 100;
}

void BattleSystem::SetTurnCost(float newTurnCost)
{
	TurnCost = newTurnCost;
}

void BattleSystem::SetPlayerTurn(bool newPlayerTurn)
{
	PlayerTurn = newPlayerTurn;
	if (PlayerTurn)
		cout << "Player's Turn" << endl;
	else
		cout << "AI's Turn" << endl;
}

float BattleSystem::GetTurnCost()
{
	return TurnCost;
}

bool BattleSystem::GetPlayerTurn()
{
	return PlayerTurn;
}

void BattleSystem::SetPlayerTroops(size_t position, CharacterEntity* Troop)
{
	std::map<size_t, CharacterEntity*>::iterator itr = PlayerTroops.find(position);
	if (itr == PlayerTroops.end())
	{
		PlayerTroops[position] = Troop;
	}
	else
		PlayerTroops.find(position)->second = Troop;
}

void BattleSystem::SetAITroops(size_t position, CharacterEntity* Troop)
{
	std::map<size_t, CharacterEntity*>::iterator itr = AITroops.find(position);
	if (itr == AITroops.end())
	{
		AITroops[position] = Troop;
	}
	AITroops.find(position)->second = Troop;
}

void BattleSystem::DamageCalculation(CharacterEntity* Attacker, Target target)
{
	/*
	map<string, CharacterEntity*>::iterator itrPlayer = player->GetAllUnitList().begin();
	map<string, CharacterEntity*>::iterator itrAI = AI->GetAIList().begin();  
	*/ 


	if (PlayerTurn)
	{
		CharacterEntity* TargetTroop = AITroops.find(target)->second;
		TargetTroop->SetHealth(TargetTroop->GetHealth() - Attacker->GetAttack());
		/*vector<CharacterEntity*>::iterator itrAI = AI->GetClassAIList(Attacker).begin();
		for (; itrAI != AI->GetAIList().end(); itrAI++)
		{
			if ((*itrAI)->GetPosition() == target)
			{
				(*itrAI)->SetHealth((*itrAI)->GetHealth() - Attacker->GetAttack());
				if ((*itrAI)->GetHealth() < 0)
					(*itrAI)->SetDefeated(true);
				break;
			}
		}*/
		//SetPlayerTurn(false);
	}
	else
	{
		CharacterEntity* TargetTroop = PlayerTroops.find(target)->second;
		TargetTroop->SetHealth(TargetTroop->GetHealth() - Attacker->GetAttack());
		/*vector<CharacterEntity*>::iterator itrPlayer = player->GetClassUnitList(Attacker).begin();
		for (; itrPlayer != player->GetUnitList().end(); itrPlayer++)
		{
			if ((*itrPlayer)->GetPosition() == target)
			{
				(*itrPlayer)->SetHealth((*itrPlayer)->GetHealth() - Attacker->GetAttack());
				if ((*itrPlayer)->GetHealth() < 0)
					(*itrPlayer)->SetDefeated(true);
				break;
			}
		}*/
		//SetPlayerTurn(true);
	}
}

void BattleSystem::SetStatusEffect(CharacterEntity* Attacker, Target target)
{
	
}