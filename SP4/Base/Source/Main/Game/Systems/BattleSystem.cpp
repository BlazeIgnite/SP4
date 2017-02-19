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

// Initialising Here
void BattleSystem::Init()
{
	SetPlayerTurn(true);
	TurnCost = 100;
}

// Setters Here
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

// Getters Here
map<size_t, CharacterEntity*>& BattleSystem::GetPlayerTroops()
{
	return PlayerTroops;
}
map<size_t, CharacterEntity*>& BattleSystem::GetAITroops()
{
	return AITroops;
}
CharacterEntity* BattleSystem::GetPlayerTroopAttacking(size_t position)
{
	return PlayerTroops.find(position)->second;
}
CharacterEntity* BattleSystem::GetAITroopAttacking(size_t position)
{
	return AITroops.find(position)->second;
}
float BattleSystem::GetTurnCost()
{
	return TurnCost;
}
bool BattleSystem::GetPlayerTurn()
{
	return PlayerTurn;
}

// Swtiching Spots in the BattleScene
void BattleSystem::SwitchSpots(map<size_t, CharacterEntity*>& TroopMap, size_t FirstPosition, size_t SecondPosition)
{
	cout << "Troop Position " << FirstPosition << " : " << TroopMap.find(FirstPosition)->second->Name << endl;
	cout << "Troop Position " << SecondPosition << " : " << TroopMap.find(SecondPosition)->second->Name << endl;
	CharacterEntity* temp = TroopMap.find(FirstPosition)->second;
	TroopMap[FirstPosition] = TroopMap[SecondPosition];
	TroopMap[SecondPosition] = temp;
	cout << "Troop Position " << FirstPosition << " : " << TroopMap.find(FirstPosition)->second->Name << endl;
	cout << "Troop Position " << SecondPosition << " : " << TroopMap.find(SecondPosition)->second->Name << endl;
}

// Battle Damage Calculation for basic attack and Skills here
void BattleSystem::DamageCalculation(CharacterEntity* Attacker, size_t target)
{
	if (PlayerTurn)
	{
		CharacterEntity* TargetTroop = AITroops.find(target)->second;
		TargetTroop->SetHealth(TargetTroop->GetHealth() - (Attacker->GetAttack() * TargetTroop->GetDamageMitigation()));
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
		for (size_t i = 0; i < PlayerTroops.size(); i++)
		{
			cout << "Troop position : " << i << " HP : " << PlayerTroops.find(i)->second->GetHealth() << endl;
		}
		cout << "AI Troops" << endl;
		for (size_t i = 0; i < AITroops.size(); i++)
		{
			cout << "Troop position : " << i << " HP : " << AITroops.find(i)->second->GetHealth() << endl;
		}
		cout << "---------------------------------------------" << endl;

		if (TargetTroop->GetHealth() < 0)
		{
			TargetTroop->SetDefeated(true);
			cout << "AI TROOP DOWN YO!" << endl;

			size_t NumberOfDefeatedTroops = 0;
			for (map<size_t, CharacterEntity*>::iterator itr = AITroops.begin(); itr != AITroops.end(); itr++)
			{
				if (itr->second->GetDefeated())
					NumberOfDefeatedTroops++;
			}
			if (NumberOfDefeatedTroops >= AITroops.size())
			{
				// Codes to switch to end Battle screen or Win screen here
				cout << "ALL AI TROOPS DOWN" << endl;
				return;
			}
		}



		SetPlayerTurn(false);
	}
	else
	{
		CharacterEntity* TargetTroop = PlayerTroops.find(target)->second;
		TargetTroop->SetHealth(TargetTroop->GetHealth() - (Attacker->GetAttack() * TargetTroop->GetDamageMitigation()));

		// Debugging
		cout << "---------------------------------------------" << endl;
		cout << "Player Troops" << endl;
		for (size_t i = 0; i < PlayerTroops.size(); i++)
		{
			cout << "Troop position : " << i << " HP : " << PlayerTroops.find(i)->second->GetHealth() << endl;
		}
		cout << "AI Troops" << endl;
		for (size_t i = 0; i < AITroops.size(); i++)
		{
			cout << "Troop position : " << i << " HP : " << AITroops.find(i)->second->GetHealth() << endl;
		}
		cout << "---------------------------------------------" << endl;

		if (TargetTroop->GetHealth() < 0)
		{
			cout << "PLAYER TROOP DOWN YO!" << endl;

			size_t NumberOfDefeatedTroops = 0;
			for (map<size_t, CharacterEntity*>::iterator itr = PlayerTroops.begin(); itr != PlayerTroops.end(); itr++)
			{
				if (itr->second->GetDefeated())
					NumberOfDefeatedTroops++;
			}
			if (NumberOfDefeatedTroops >= PlayerTroops.size())
			{
				// Codes to switch to Lose screen here
				cout << "ALL PLAYER TROOPS DOWN" << endl;
				return;
			}
		}
		SetPlayerTurn(true);
	}
}
void BattleSystem::DamageCalculation(CharacterEntity* Attacker, size_t target, Ability* AttackerSkill)
{
	if (PlayerTurn)
	{
		//Place shift codes here
		AttackerSkill->ApplyAbility(Attacker,GetAITroops().at(target));

		cout << "---------------------------------------------" << endl;
		cout << "Player Troops" << endl;
		for (size_t i = 0; i < PlayerTroops.size(); i++)
		{
			cout << "Troop position : " << i << " HP : " << PlayerTroops.find(i)->second->GetHealth() << endl;
		}
		cout << "AI Troops" << endl;
		for (size_t i = 0; i < AITroops.size(); i++)
		{
			cout << "Troop position : " << i << " HP : " << AITroops.find(i)->second->GetHealth() << endl;
		}
	}
	else
	{
	}
}

// Dealing any status Effect to opponent goes here
void BattleSystem::SetStatusEffect(CharacterEntity* Attacker, size_t target)
{
	
}