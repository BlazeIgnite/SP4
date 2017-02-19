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
	SelectedTroop = NULL;
	SetTurnCost(100);
	SetPlayerTurn(true);
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
void BattleSystem::SetSelectedTroop(CharacterEntity* newSelectedTroop)
{
	SelectedTroop = newSelectedTroop;
}
void BattleSystem::SetTurnCost(size_t newTurnCost)
{
	TurnCost = newTurnCost;
}
void BattleSystem::SetPlayerTurn(bool newPlayerTurn)
{
	SetTurnCost(100);
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
CharacterEntity* BattleSystem::GetSelectedTroop()
{
	return SelectedTroop;
}
size_t BattleSystem::GetTurnCost()
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
void BattleSystem::MoveTroopBackByOne(map<size_t, CharacterEntity*>& TroopMap)
{
	SwitchSpots(TroopMap, 0, 1);
	SwitchSpots(TroopMap, 0, 2);
}
void BattleSystem::MoveTroopBackByTwo(map<size_t, CharacterEntity*>& TroopMap)
{
	SwitchSpots(TroopMap, 0, 2);
	SwitchSpots(TroopMap, 0, 1);
}
void BattleSystem::MoveTroopFrontByOne(map<size_t, CharacterEntity*>& TroopMap)
{
	MoveTroopBackByTwo(TroopMap);
}
void BattleSystem::MoveTroopFrontByTwo(map<size_t, CharacterEntity*>& TroopMap)
{
	MoveTroopBackByOne(TroopMap);
}


// Battle Damage Calculation for basic attack and Skills here
void BattleSystem::DamageCalculation(CharacterEntity* Attacker, size_t target)
{
	if (PlayerTurn)
	{
		CharacterEntity* TargetTroop = AITroops.find(target)->second;
		TargetTroop->SetHealth(TargetTroop->GetHealth() - (Attacker->GetAttack() * TargetTroop->GetDamageMitigation()));
		// One more line of code needed, the default attack cost put here
		// TurnCost -= AttackCost;

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

		// One more line of code needed, the default attack cost put here
		// TurnCost -= AttackCost;

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
void BattleSystem::DamageCalculation(CharacterEntity* Attacker, size_t target, Skill* AttackerSkill)
{
	if (PlayerTurn)
	{
		//Place shift codes here
		if (AttackerSkill->shiftposition != 0)
		{
			if (AttackerSkill->shiftposition == 1)
				MoveTroopBackByOne(AITroops);
			else if (AttackerSkill->shiftposition == 2)
				MoveTroopBackByTwo(AITroops);
			else if (AttackerSkill->shiftposition == -1)
				MoveTroopFrontByOne(AITroops);
			else if (AttackerSkill->shiftposition == -2)
				MoveTroopFrontByTwo(AITroops);
		}
		AttackerSkill->SkillBehavior();
	}
	else
	{
	}
}

/*
*
*	Function: ApplyFriendlyEffect
*	Purpose: Any Buffs or healing goes into this function
*
*	When to be called: When healing or buff to teammate is done
*
*/
void BattleSystem::ApplyFriendlyEffect(map<size_t, CharacterEntity*>& TeamMap, CharacterEntity* User, size_t TargettedTeammate)
{
	// Logic to maybe Healing or applying friendly effect here
	// SkillOfUser->ApplyEffect(TeamMap.find(TargettedTeammate)->second);
}


// Dealing any status Effect to opponent goes here
/*
*
*	Function: SetStatusEffect
*	Purpose: It finds the Certain Troop to be affected by a status effect. Pass in the team and the target
*
*	When to be called: It should be called when any troop wants to set a status effect to opponent, if its not called within the BattleSystem, either player is hacking or we are bad at coding
*
*/
void BattleSystem::SetStatusEffect(map<size_t, CharacterEntity*>& TeamMap, size_t target)
{
	// Set the status Effect of the Character Entity Here
	//TeamMap.find(target)->second->SetStatusEffect( stun? / poison? / burn?);
}

/*
*
*	Function: Reset
*	Purpose: Empties the maps of battle scene
*
*	When to be called: ONLY call it after Battle is completed
*
*/
void BattleSystem::Reset()
{
	SetTurnCost(100);
	PlayerTroops.clear();
	AITroops.clear();
}