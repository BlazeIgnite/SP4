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
	SelectedSkill = NULL;
	SetTurnCost(100);
	PlayerTurn = true;
	PlayerWon = false;	
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
	else
		AITroops.find(position)->second = Troop;
}
void BattleSystem::SetPlayerTroopSkills(size_t playerPosition, size_t skillPosition, Skill* skill)
{
	map<size_t, map<size_t, Skill*>>::iterator itr = PlayerTroopSkills.find(playerPosition);
	map<size_t, Skill*>::iterator itr2 = PlayerTroopSkills.find(playerPosition)->second.begin();
	if (itr == PlayerTroopSkills.end())
	{
		map<size_t, Skill*> EmptySkillMap;
		EmptySkillMap[skillPosition] = skill;
		PlayerTroopSkills[playerPosition] = EmptySkillMap;
	}
	else
	{
		if (itr2 == PlayerTroopSkills.find(playerPosition)->second.end())
			PlayerTroopSkills.find(playerPosition)->second[skillPosition] = skill;
		else
			PlayerTroopSkills.find(playerPosition)->second.at(skillPosition) = skill;
	}
}

size_t BattleSystem::GetSelectedTroopPosition()
{
	for (map<size_t, CharacterEntity*>::iterator it = PlayerTroops.begin(); it != PlayerTroops.end(); it++)
	{
		if (SelectedTroop == it->second)
			return it->first;
	}
	return NULL;
}

size_t BattleSystem::GetNumberOfAITroopAlive()
{
	size_t NumberofAliveTroops = 0;
	for (map<size_t, CharacterEntity*>::iterator itr = AITroops.begin(); itr != AITroops.end(); itr++)
	{
		// Find Out Position of defeated troop
		// Do push back or front to set the troop that are alive to the front
		if (!itr->second->GetDefeated())
			NumberofAliveTroops++;
	}
	return NumberofAliveTroops;
}

void BattleSystem::SetPlayerTurn(bool newPlayerTurn)
{
	SetTurnCost(100);

	if (PlayerTurn)
	{
		for (map<size_t, CharacterEntity*>::iterator it = PlayerTroops.begin(); it != PlayerTroops.end(); it++)
		{
			vector<Skill*> SkillList = it->second->GetSkillList();
			for (vector<Skill*>::iterator it2 = SkillList.begin(); it2 != SkillList.end(); it2++)
			{
				if ((*it2)->GetTurnCooldown() > 0)
					(*it2)->SetTurnCooldown((*it2)->GetTurnCooldown() - 1);
			}

			if (it->second->GetStunned())
			{
				if (it->second->GetStunTimer() > 0)
				{
					it->second->SetStunTimer(it->second->GetStunTimer() - 1);
					if (it->second->GetStunTimer() == 0)
						it->second->SetStunned(false);
				}
			}
			if (it->second->GetBleeding())
			{
				if (it->second->GetBleedTimer() > 0)
				{
					it->second->SetBleedTimer(it->second->GetBleedTimer() - 1);
					it->second->BleedEffect();
					if (it->second->GetBleedTimer() == 0)
					{
						it->second->SetBleeding(false);
					}
				}
			}
			if (it->second->GetBuffed())
			{
				if (it->second->GetBuffTimer() > 0)
				{
					it->second->SetBuffTimer(it->second->GetBuffTimer() - 1);
					if (it->second->GetBuffTimer() == 0)
						it->second->SetBuffed(false);
				}
			}
			if (it->second->GetDebuffed())
			{
				if (it->second->GetStunTimer() > 0)
				{
					it->second->SetDebuffTimer(it->second->GetDebuffed() - 1);
					if (it->second->GetDebuffed() == 0)
						it->second->SetDebuffed(false);
				}
			}
		}
	}
	else
	{
		for (map<size_t, CharacterEntity*>::iterator it = AITroops.begin(); it != AITroops.end(); it++)
		{
			vector<Skill*> SkillList = it->second->GetSkillList();
			for (vector<Skill*>::iterator it2 = SkillList.begin(); it2 != SkillList.end(); it2++)
			{
				if ((*it2)->GetTurnCooldown() > 0)
					(*it2)->SetTurnCooldown((*it2)->GetTurnCooldown() - 1);
			}

			if (it->second->GetStunned())
			{
				if (it->second->GetStunTimer() > 0)
				{
					it->second->SetStunTimer(it->second->GetStunTimer() - 1);
					if (it->second->GetStunTimer() == 0)
					{
						it->second->SetStunned(false);
					}
				}
			}
			if (it->second->GetBleeding())
			{
				if (it->second->GetBleedTimer() > 0)
				{
					it->second->SetBleedTimer(it->second->GetBleedTimer() - 1);
					it->second->BleedEffect();
					if (it->second->GetBleedTimer() == 0)
					{
						it->second->SetBleeding(false);
					}
				}
			}
			if (it->second->GetBuffed())
			{
				if (it->second->GetBuffTimer() > 0)
				{
					it->second->SetBuffTimer(it->second->GetBuffTimer() - 1);
					if (it->second->GetBuffTimer() == 0)
					{
						it->second->SetBuffed(false);
						it->second->ResetStats();
					}
				}
			}
			if (it->second->GetDebuffed())
			{
				if (it->second->GetStunTimer() > 0)
				{
					it->second->SetDebuffTimer(it->second->GetDebuffed() - 1);
					if (it->second->GetDebuffed() == 0)
					{
						it->second->SetDebuffed(false);
						it->second->ResetStats();
					}
				}
			}
		}
	}

	Debugging();

	SelectedTroop = NULL;
	SelectedEnemyTroop = NULL;
	PlayerTurn = newPlayerTurn;
}


// Swtiching Spots in the BattleScene
void BattleSystem::SwitchSpots(map<size_t, CharacterEntity*>& TroopMap, size_t FirstPosition, size_t SecondPosition)
{
	CharacterEntity* temp = TroopMap.find(FirstPosition)->second;
	Vector3 tempPos = TroopMap.find(FirstPosition)->second->GetVectorPosition();
	TroopMap[FirstPosition]->SetPosition(TroopMap[SecondPosition]->GetVectorPosition());
	TroopMap[FirstPosition] = TroopMap[SecondPosition];
	TroopMap[SecondPosition]->SetPosition(tempPos);
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
void BattleSystem::DamageCalculation(size_t target, Skill* AttackerSkill)
{
	if (PlayerTurn)
	{
		CharacterEntity* targettroop = AITroops.find(target)->second;
		int tempHealth = targettroop->GetHealth() - AttackerSkill->GetDamage();
		if (tempHealth <= 0)
			tempHealth = 0;
		targettroop->SetHealth(tempHealth);
		SetStatusEffect(target, AttackerSkill);
		TurnCost -= AttackerSkill->GetActionCost();
		if (targettroop->GetHealth() < 1)
		{
			targettroop->SetDefeated(true);
			size_t NumberofDefeatedTroops = 0;
			for (map<size_t, CharacterEntity*>::iterator itr = AITroops.begin(); itr != AITroops.end(); itr++)
			{
				// Find Out Position of defeated troop
				// Do push back or front to set the troop that are alive to the front
				if (itr->second->GetDefeated())
					NumberofDefeatedTroops++;
			}
			if (NumberofDefeatedTroops == 1)
			{
				if (AITroops.find(target)->first == 0)
					MoveTroopFrontByOne(AITroops);
				else if (AITroops.find(target)->first == 1)
					SwitchSpots(AITroops, AITroops.find(target)->first, AITroops.find(target + 1)->first);
			}
			else if (NumberofDefeatedTroops == 2)
			{
				if (AITroops.find(target)->first == 0)
					MoveTroopFrontByOne(AITroops);
			}
			else if (NumberofDefeatedTroops >= AITroops.size())
			{
				//Go to win screen;
				return;
			}
		}
	}
	else
	{
		CharacterEntity* targettroop = PlayerTroops.find(target)->second; 
		int tempHealth = targettroop->GetHealth() - AttackerSkill->GetDamage();
		if (tempHealth <= 0)
			tempHealth = 0;
		targettroop->SetHealth(tempHealth);
		SetStatusEffect(target, AttackerSkill);
		TurnCost -= AttackerSkill->GetActionCost();
		if (targettroop->GetHealth() < 1)
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
			}
			if (NumberofDefeatedTroops == 1)
			{
				if (PlayerTroops.find(target)->first == 0)
					MoveTroopFrontByOne(PlayerTroops);
				else if (PlayerTroops.find(target)->first == 1)
					SwitchSpots(PlayerTroops, PlayerTroops.find(target)->first, PlayerTroops.find(target + 1)->first);
			}
			else if (NumberofDefeatedTroops == 2)
			{
				if (PlayerTroops.find(target)->first == 0)
					MoveTroopFrontByOne(PlayerTroops);
			}
			else if (NumberofDefeatedTroops >= PlayerTroops.size())
			{
				//Go to lose screen;
				return;
			}
		}
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
				if (AttackerSkill->GetSelectableTarget(target) && AttackerSkill->GetRequiredPosition((*it).first) && AttackerSkill->GetTurnCooldown() <= 0)
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
				if (AttackerSkill->GetSelectableTarget(target) && AttackerSkill->GetRequiredPosition((*it).first) && AttackerSkill->GetTurnCooldown() <= 0)
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
void BattleSystem::ApplyFriendlyEffect(size_t TargettedTeammate, Skill* SkillUsed)
{
	// Logic to maybe Healing or applying friendly effect here
	/*for (map<size_t, CharacterEntity*>::iterator itr = TeamMap.begin(); itr != TeamMap.end(); itr++)
	{
		CharacterEntity* character = itr->second;
		character->SetBuffed(true);
		character->SetBuffTimer(SkillUsed->GetStatusEffectTimer());
	}*/

	if (PlayerTurn)
	{
		PlayerTroops.at(TargettedTeammate)->SetHealth(PlayerTroops.at(TargettedTeammate)->GetHealth() + SkillUsed->GetHeal());
		if (SkillUsed->StatusEffectExistence("Buff"))
		{
			PlayerTroops.at(TargettedTeammate)->SetBuffed(true);
			PlayerTroops.at(TargettedTeammate)->SetBuffTimer(SkillUsed->GetStatusEffectTimer("Buff"));
		}
	}
	else
	{
		AITroops.at(TargettedTeammate)->SetHealth(AITroops.at(TargettedTeammate)->GetHealth() + SkillUsed->GetHeal());
		if (SkillUsed->StatusEffectExistence("Buff"))
		{
			AITroops.at(TargettedTeammate)->SetBuffed(true);
			AITroops.at(TargettedTeammate)->SetBuffTimer(SkillUsed->GetStatusEffectTimer("Buff"));
		}
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
void BattleSystem::SetStatusEffect(size_t target, Skill* SkillUsed)
{
	// Set the status Effect of the Character Entity Here
	//TeamMap.find(target)->second->SetStatusEffect( stun? / poison? / burn?);
	
	if (PlayerTurn)
	{
		if (SkillUsed->StatusEffectExistence("Debuff"))
		{
			AITroops.at(target)->SetBuffed(true);
			AITroops.at(target)->SetBuffTimer(SkillUsed->GetStatusEffectTimer("Debuff"));
		}
		if (SkillUsed->StatusEffectExistence("Stun"))
		{
			AITroops.at(target)->SetStunned(true);
			AITroops.at(target)->SetBuffTimer(SkillUsed->GetStatusEffectTimer("Stun"));
		}
		if (SkillUsed->StatusEffectExistence("Bleed"))
		{
			AITroops.at(target)->SetBleeding(true);
			AITroops.at(target)->SetBuffTimer(SkillUsed->GetStatusEffectTimer("Bleed"));
		}
	}
	else
	{
		if (SkillUsed->StatusEffectExistence("Debuff"))
		{
			PlayerTroops.at(target)->SetBuffed(true);
			PlayerTroops.at(target)->SetBuffTimer(SkillUsed->GetStatusEffectTimer("Debuff"));
		}
		if (SkillUsed->StatusEffectExistence("Stun"))
		{
			PlayerTroops.at(target)->SetStunned(true);
			PlayerTroops.at(target)->SetBuffTimer(SkillUsed->GetStatusEffectTimer("Stun"));
		}
		if (SkillUsed->StatusEffectExistence("Bleed"))
		{
			PlayerTroops.at(target)->SetBleeding(true);
			PlayerTroops.at(target)->SetBuffTimer(SkillUsed->GetStatusEffectTimer("Bleed"));
		}
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
	SelectedTroop = NULL;
	SelectedEnemyTroop = NULL;
	SetTurnCost(100);
	PlayerTroops.clear();
	AITroops.clear();
}

void BattleSystem::Debugging()
{
	cout << "/*****************************************/" << endl;
	for (size_t i = 0; i < PlayerTroops.size(); i++)
	{
		cout << "Player Troop " << i << " : " << PlayerTroops.at(i)->GetName() << endl;
		cout << "Health : " << PlayerTroops.at(i)->GetHealth() << endl;
	}

	for (size_t i = 0; i < AITroops.size(); i++)
	{
		cout << "Player Troop " << i << " : " << AITroops.at(i)->GetName() << endl;
		cout << "Health : " << AITroops.at(i)->GetHealth() << endl;
		cout << "Damage : " << AITroops.at(i)->GetSkillInVector("Basic Attack")->GetDamage() << endl;
	}

	cout << "/*****************************************/" << endl;
}