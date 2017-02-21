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
		Troop->SetPosition(Vector3(ObjectManager::Instance().WorldWidth * (0.3f - (position * 0.1)), ObjectManager::Instance().WorldHeight * 0.5f, 0.f));
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
		Troop->SetPosition(Vector3(ObjectManager::Instance().WorldWidth * (0.7f + (position * 0.1)), ObjectManager::Instance().WorldHeight * 0.5f, 0.f));
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

			size_t NumberOfDefeatedTroops = 0;
			for (map<size_t, CharacterEntity*>::iterator itr = AITroops.begin(); itr != AITroops.end(); itr++)
			{
				if (itr->second->GetDefeated())
					NumberOfDefeatedTroops++;
			}
			if (NumberOfDefeatedTroops >= AITroops.size())
			{
				// Codes to switch to end Battle screen or Win screen here
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
			size_t NumberOfDefeatedTroops = 0;
			for (map<size_t, CharacterEntity*>::iterator itr = PlayerTroops.begin(); itr != PlayerTroops.end(); itr++)
			{
				if (itr->second->GetDefeated())
					NumberOfDefeatedTroops++;
			}
			if (NumberOfDefeatedTroops >= PlayerTroops.size())
			{
				// Codes to switch to Lose screen here
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
		for (map<size_t, CharacterEntity*>::iterator itr = PlayerTroops.begin(); itr != PlayerTroops.end(); itr++)
		{
			if (itr->second = Attacker)
			{
				CharacterEntity* targettroop = AITroops.find(target)->second;
				if (AttackerSkill->GetRequiredPosition(itr->first) == 1 && AttackerSkill->GetSelectableTarget(target) == 1)
				{
					targettroop->SetHealth(targettroop->GetHealth() - (AttackerSkill->GetDamage() * targettroop->GetDamageMitigation()));
					if (targettroop <= 0)
					{
						targettroop->SetDefeated(true);
						size_t NumberofDefeatedTroops = 0;
						for (map<size_t, CharacterEntity*>::iterator itr = AITroops.begin(); itr != AITroops.end(); itr++)
						{
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
					}
					SetPlayerTurn(false);
				}

			}
		}
		
	}
	else
	{
		CharacterEntity* targettroop = PlayerTroops.find(target)->second;
		targettroop->SetHealth(targettroop->GetHealth() - (AttackerSkill->GetDamage() * targettroop->GetDamageMitigation()));
		if (targettroop <= 0)
		{
			targettroop->SetDefeated(true);
			size_t NumberofDefeatedTroops = 0;
			for (map<size_t, CharacterEntity*>::iterator itr = PlayerTroops.begin(); itr != PlayerTroops.end(); itr++)
			{
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