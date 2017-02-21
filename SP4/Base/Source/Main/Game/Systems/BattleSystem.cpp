#include "BattleSystem.h"
#include "ObjectManager.h"
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
	SelectedEnemyTroop = NULL;
	SetTurnCost(100);
	SetPlayerTurn(true);
	SetPlayerWon(true);
}

// Setters Here
void BattleSystem::SetPlayerTroops(size_t position, CharacterEntity* Troop)
{
	std::map<size_t, CharacterEntity*>::iterator itr = PlayerTroops.find(position);
	if (itr == PlayerTroops.end())
	{
		PlayerTroops[position] = Troop;
		Troop->SetPosition(Vector3(ObjectManager::Instance().WorldWidth * (0.3f - (position * 0.1f)), ObjectManager::Instance().WorldHeight * 0.5f, 0.f));
	}
	else
	{
		PlayerTroops.find(position)->second = Troop;
		//Troop->SetPosition(Vector3(ObjectManager::Instance().WorldWidth * 0.3f, ObjectManager::Instance().WorldHeight * 0.5f, -5.f));
	}

		
}
void BattleSystem::SetAITroops(size_t position, CharacterEntity* Troop)
{
	std::map<size_t, CharacterEntity*>::iterator itr = AITroops.find(position);
	if (itr == AITroops.end())
	{
		AITroops[position] = Troop;
		Troop->SetPosition(Vector3(ObjectManager::Instance().WorldWidth * (0.7f + (position * 0.1f)), ObjectManager::Instance().WorldHeight * 0.5f, 0.f));
	}
	AITroops.find(position)->second = Troop;
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


// Swtiching Spots in the BattleScene
void BattleSystem::SwitchSpots(map<size_t, CharacterEntity*>& TroopMap, size_t FirstPosition, size_t SecondPosition)
{
	CharacterEntity* temp = TroopMap.find(FirstPosition)->second;
	TroopMap[FirstPosition] = TroopMap[SecondPosition];
	TroopMap[SecondPosition] = temp;
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
void BattleSystem::DamageCalculation(CharacterEntity* Attacker, size_t target, Skill* AttackerSkill)
{
	if (PlayerTurn)
	{
		CharacterEntity* targettroop = AITroops.find(target)->second;
		targettroop->SetHealth(targettroop->GetHealth() - (AttackerSkill->GetDamage() * targettroop->GetDamageMitigation()));
		TurnCost -= AttackerSkill->GetActionCost();
		if (targettroop <= 0)
		{
			targettroop->SetDefeated(true);
			size_t NumberofDefeatedTroops = 0;
			for (map<size_t, CharacterEntity*>::iterator itr = AITroops.begin(); itr != AITroops.end(); itr++)
			{
				// Find Out Position of defeated troop
				// Do push back or front to set the troop that are alive to the front
				if (itr->second->GetDefeated())
				{
					NumberofDefeatedTroops++;
				}
				if (NumberofDefeatedTroops >= AITroops.size())
				{
					//Go to win screen;
					return;
				}
			}
		SetPlayerTurn(false);
		}
	}
	else
	{
		CharacterEntity* targettroop = PlayerTroops.find(target)->second;
		targettroop->SetHealth(targettroop->GetHealth() - (AttackerSkill->GetDamage() * targettroop->GetDamageMitigation()));
		TurnCost -= AttackerSkill->GetActionCost();
		if (targettroop <= 0)
		{
			targettroop->SetDefeated(true);
			size_t NumberofDefeatedTroops = 0;
			for (map<size_t, CharacterEntity*>::iterator itr = PlayerTroops.begin(); itr != PlayerTroops.end(); itr++)
			{
				// Find Out Position of defeated troop
				// Do push back or front to set the troop that are alive to the front
				if (itr->second->GetDefeated())
				{
					NumberofDefeatedTroops++;
				}
				if (NumberofDefeatedTroops >= PlayerTroops.size())
				{
					//Go to lose screen;
					return;
				}
			}
		}
		SetPlayerTurn(true);
	}
}

bool BattleSystem::CanActivateSkill(CharacterEntity* Attacker, size_t target, Skill* AttackerSkill)
{
	if (PlayerTurn)
	{
		for (map<size_t, CharacterEntity*>::iterator it = AITroops.begin(); it != AITroops.end(); it++)
		{
			if ((*it).second == Attacker)
			{
				if (AttackerSkill->GetSelectableTarget(target) && AttackerSkill->GetRequiredPosition((*it).first))
					return true;
			}
		}
		return false;
	}
	else
	{
		for (map<size_t, CharacterEntity*>::iterator it = PlayerTroops.begin(); it != PlayerTroops.end(); it++)
		{
			if ((*it).second == Attacker)
			{
				if (AttackerSkill->GetSelectableTarget(target) && AttackerSkill->GetRequiredPosition((*it).first))
					return true;
			}
		}
		return false;
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
	for (map<size_t, CharacterEntity*>::iterator itr = TeamMap.begin(); itr != TeamMap.end(); itr++)
	{
		CharacterEntity* character = itr->second;
		character->SetBuffed(true);
	}
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
	for (map<size_t, CharacterEntity*>::iterator itr = TeamMap.begin(); itr != TeamMap.end(); itr++)
	{
		CharacterEntity* character = itr->second;
		character->SetBleeding(true);
		character->SetStunned(true);
		character->SetDebuffed(true);
	}
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