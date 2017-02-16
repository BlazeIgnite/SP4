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

void BattleSystem::DamageCalculation(CharacterEntity* Attacker, int target)
{
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

		// Debugging
		cout << "---------------------------------------------" << endl;
		cout << "Player Troops" << endl;
		for (int i = 0; i < PlayerTroops.size(); i++)
		{
			cout << "Troop position : " << i << " HP : " << PlayerTroops.find(i)->second->GetHealth() << endl;
		}
		cout << "AI Troops" << endl;
		for (int i = 0; i < AITroops.size(); i++)
		{
			cout << "Troop position : " << i << " HP : " << AITroops.find(i)->second->GetHealth() << endl;
		}
		cout << "---------------------------------------------" << endl;

		if (TargetTroop->GetHealth() < 0)
			cout << "TROOP DOWN YO!" << endl;
		SetPlayerTurn(false);
	}
	else
	{
		CharacterEntity* TargetTroop = PlayerTroops.find(target)->second;
		TargetTroop->SetHealth(TargetTroop->GetHealth() - Attacker->GetAttack());

		// Debugging
		cout << "---------------------------------------------" << endl;
		cout << "Player Troops" << endl;
		for (int i = 0; i < PlayerTroops.size(); i++)
		{
			cout << "Troop position : " << i << " HP : " << PlayerTroops.find(i)->second->GetHealth() << endl;
		}
		cout << "AI Troops" << endl;
		for (int i = 0; i < AITroops.size(); i++)
		{
			cout << "Troop position : " << i << " HP : " << AITroops.find(i)->second->GetHealth() << endl;
		}
		cout << "---------------------------------------------" << endl;

		if (TargetTroop->GetHealth() < 0)
			cout << "TROOP DOWN YO!" << endl;
		SetPlayerTurn(true);
	}
}

void BattleSystem::SetStatusEffect(CharacterEntity* Attacker, int target)
{
	
}

CharacterEntity* BattleSystem::GetPlayerTroopAttacking(size_t position)
{
	return PlayerTroops.find(position)->second;
}

CharacterEntity* BattleSystem::GetAITroopAttacking(size_t position)
{
	return AITroops.find(position)->second;
}