#include "BattleSystem.h"
#include "ObjectManager.h"
#include "../../Base/Source/Main/Engine/System/SceneSystem.h"
#include "../Audio/Audio_Player.h"
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
	PlayerWon = 0;
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
}
void BattleSystem::SetAITroops(size_t position, CharacterEntity* Troop)
{
	std::map<size_t, CharacterEntity*>::iterator itr = AITroops.find(position);
	if (itr == AITroops.end())
	{
		AITroops[position] = Troop;
		Troop->SetPosition(Vector3(ObjectManager::Instance().WorldWidth * (0.7f + (position * 0.1f)), ObjectManager::Instance().WorldHeight * 0.5f, 0.f));
	}
}
void BattleSystem::SetPlayerTroopSkills(size_t playerPosition, size_t skillPosition)
{
	map<size_t, map<size_t, Skill*>>::iterator itr = PlayerTroopSkills.find(playerPosition);
	vector<Skill*>* temp = PlayerTroops.find(playerPosition)->second->GetSkillList();
	if (temp->size() <= skillPosition)
		return;
	vector<Skill*>::iterator SkillIt = temp->begin();
	for (size_t i = 0; SkillIt != temp->end(); SkillIt++)
	{
		if (i == skillPosition)
			break;
		i++;
	}

	if (itr == PlayerTroopSkills.end())
	{
		map<size_t, Skill*> EmptySkillMap;
		EmptySkillMap[skillPosition] = (*SkillIt);
		PlayerTroopSkills[playerPosition] = EmptySkillMap;
	}
	else
	{
		map<size_t, Skill*>::iterator itr2 = itr->second.find(skillPosition);
		if (itr2 == itr->second.end())
			PlayerTroopSkills.find(playerPosition)->second[skillPosition] = (*SkillIt);
		else
			PlayerTroopSkills.find(playerPosition)->second.at(skillPosition) = (*SkillIt);
	}
}
void BattleSystem::SetSelectedTroop(CharacterEntity* newSelectedTroop)
{
	SelectedTroop = newSelectedTroop;
	for (map<size_t, CharacterEntity*>::iterator it = PlayerTroops.begin(); it != PlayerTroops.end(); it++)
	{
		if (SelectedTroop == it->second)
			DisplaySkillNum = it->first;
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

size_t BattleSystem::GetNumberOfPlayerTroopAlive()
{
	size_t NumberofAliveTroops = 0;
	for (map<size_t, CharacterEntity*>::iterator itr = PlayerTroops.begin(); itr != PlayerTroops.end(); itr++)
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
	TurnCost = 100;
	SelectedTroop = NULL;
	SelectedEnemyTroop = NULL;
	SelectedSkill = NULL;

	if (PlayerTurn)
	{
		for (map<size_t, CharacterEntity*>::iterator it = PlayerTroops.begin(); it != PlayerTroops.end(); it++)
		{
			vector<Skill*>* SkillList = it->second->GetSkillList();
			for (vector<Skill*>::iterator it2 = SkillList->begin(); it2 != SkillList->end(); it2++)
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
				it->second->SetHealth(it->second->GetLevel() + 2);
				if (it->second->GetBleedTimer() > 0)
				{
					it->second->SetBleedTimer(it->second->GetBleedTimer() - 1);
					it->second->BleedEffect();
					if (it->second->GetBleedTimer() == 0)
						it->second->SetBleeding(false);
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
				if (it->second->GetDebuffTimer() > 0)
				{
					it->second->SetDebuffTimer(it->second->GetDebuffed() - 1);
					if (it->second->GetDebuffTimer() == 0)
						it->second->SetDebuffed(false);
				}
			}
		}
	}
	else
	{
		for (map<size_t, CharacterEntity*>::iterator it = AITroops.begin(); it != AITroops.end(); it++)
		{
			vector<Skill*>* SkillList = it->second->GetSkillList();
			for (vector<Skill*>::iterator it2 = SkillList->begin(); it2 != SkillList->end(); it2++)
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
				it->second->SetHealth(it->second->GetLevel() + 2);
				if (it->second->GetBleedTimer() > 0)
				{
					it->second->SetBleedTimer(it->second->GetBleedTimer() - 1);
					it->second->BleedEffect();
					if (it->second->GetBleedTimer() == 0)
						it->second->SetBleeding(false);
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


	PlayerTurn = newPlayerTurn;
	Debugging();
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
	if (TroopMap.size() > 2)
		SwitchSpots(TroopMap, 0, 2);
}
void BattleSystem::MoveTroopBackByTwo(map<size_t, CharacterEntity*>& TroopMap)
{
	if (TroopMap.size() > 2)
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
size_t BattleSystem::DamageCalculation(size_t target, Skill* AttackerSkill)
{
	size_t damage = AttackerSkill->GetDamage();
	AttackerSkill->SetTurnCooldown(AttackerSkill->GetMaxTurnCooldown());
	if (PlayerTurn)
	{
		CharacterEntity* targettroop = AITroops.find(target)->second;
		int tempHealth = targettroop->GetHealth() - damage;
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
			if (NumberofDefeatedTroops >= AITroops.size())
			{
				//Go to win screen;
				SceneSystem::Instance().SwitchScene("Town_Scene");
				for (map<size_t, CharacterEntity*>::iterator i = AITroops.begin(); i != AITroops.end(); i++)
				{
					if (i->second != nullptr)
					{
						delete i->second;
						i->second = NULL;
					}
				}
				Reset();
				return damage;
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
		}
		return damage;
	}
	else
	{
		CharacterEntity* targettroop = PlayerTroops.find(target)->second; 
		int tempHealth = targettroop->GetHealth() - damage;
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
			if (NumberofDefeatedTroops >= PlayerTroops.size())
			{
				//Go to lose screen;
				SceneSystem::Instance().SwitchScene("Town_Scene");

				return damage;
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
		}
		return damage;
	}
	return 0;
}

bool BattleSystem::CanActivateSkill(CharacterEntity* Attacker, size_t target, Skill* AttackerSkill)
{
	if (Attacker == NULL || AttackerSkill == NULL)
		return false;
	if (PlayerTurn)
	{
		for (map<size_t, CharacterEntity*>::iterator it = PlayerTroops.begin(); it != PlayerTroops.end(); it++)
		{
			if ((*it).second == Attacker)
			{
				if (!Attacker->GetStunned() && !Attacker->GetDefeated())
				{
					int temp = TurnCost - AttackerSkill->GetActionCost();

					std::cout << AttackerSkill->GetTurnCooldown() << std::endl;
					if (temp < 0)
					{
						std::cout << "Not Enough Cost" << std::endl;
						return false;
					}
					else
					{
						if (AttackerSkill->GetTurnCooldown() == 0)
						{
							if (AttackerSkill->GetRequiredPosition((*it).first))
							{
								if (AttackerSkill->GetSelectableTarget(target))
								{
									AttackerSkill->SetTurnCooldown(AttackerSkill->GetMaxTurnCooldown());
									return true;
								}
								else
								{
									std::cout << "Target not affected by skill" << std::endl;
									return false;
								}
							}
							else
							{
								std::cout << "Skill unable to use on Position" << std::endl;
								return false;
							}
						}
						else
						{
							std::cout << "Skill still on Cooldown" << std::endl;
							return false;
						}
						
					}
				}
				else
				{
					std::cout << "Target is Defeated" << std::endl;
					return false;
				}
			}
		}
		return false;
	}
	else
	{
		for (map<size_t, CharacterEntity*>::iterator it = AITroops.begin(); it != AITroops.end(); it++)
		{
			if ((*it).second == Attacker)
			{
				if (!Attacker->GetStunned() && !Attacker->GetDefeated())
				{
					if (AttackerSkill->GetSelectableTarget(target) && AttackerSkill->GetRequiredPosition((*it).first) && AttackerSkill->GetTurnCooldown() <= 0 && (TurnCost - AttackerSkill->GetActionCost() >= 0))
						return true;
				}
				else
					return false;
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
			//AudioPlayer::Instance().PlayBuffEffect();
		}
	}
	else
	{
		AITroops.at(TargettedTeammate)->SetHealth(AITroops.at(TargettedTeammate)->GetHealth() + SkillUsed->GetHeal());
		if (SkillUsed->StatusEffectExistence("Buff"))
		{
			AITroops.at(TargettedTeammate)->SetBuffed(true);
			AITroops.at(TargettedTeammate)->SetBuffTimer(SkillUsed->GetStatusEffectTimer("Buff"));
			//AudioPlayer::Instance().PlayBuffEffect();
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
			AITroops.at(target)->SetDebuffed(true);
			AITroops.at(target)->SetDebuffTimer(SkillUsed->GetStatusEffectTimer("Debuff"));
			AudioPlayer::Instance().PlayDebuffEffect();
		}
		if (SkillUsed->StatusEffectExistence("Stun"))
		{
			AITroops.at(target)->SetStunned(true);
			AITroops.at(target)->SetBuffTimer(SkillUsed->GetStatusEffectTimer("Stun"));
			AudioPlayer::Instance().PlayStunEffect();
		}
		if (SkillUsed->StatusEffectExistence("Bleed"))
		{
			AITroops.at(target)->SetBleeding(true);
			AITroops.at(target)->SetBuffTimer(SkillUsed->GetStatusEffectTimer("Bleed"));
			AudioPlayer::Instance().PlayBleedEffect();
		}
	}
	else
	{
		if (SkillUsed->StatusEffectExistence("Debuff"))
		{
			PlayerTroops.at(target)->SetBuffed(true);
			PlayerTroops.at(target)->SetBuffTimer(SkillUsed->GetStatusEffectTimer("Debuff"));
			AudioPlayer::Instance().PlayDebuffEffect();
		}
		if (SkillUsed->StatusEffectExistence("Stun"))
		{
			PlayerTroops.at(target)->SetStunned(true);
			PlayerTroops.at(target)->SetBuffTimer(SkillUsed->GetStatusEffectTimer("Stun"));
			AudioPlayer::Instance().PlayStunEffect();
		}
		if (SkillUsed->StatusEffectExistence("Bleed"))
		{
			PlayerTroops.at(target)->SetBleeding(true);
			PlayerTroops.at(target)->SetBuffTimer(SkillUsed->GetStatusEffectTimer("Bleed"));
			AudioPlayer::Instance().PlayBleedEffect();
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
	SelectedSkill = NULL;
	SetTurnCost(100);
	for (auto it : AITroops)
	{
		if (it.second != nullptr)
			delete it.second;
		it.second = nullptr;
	}
	PlayerTroops.clear();
	AITroops.clear();
	PlayerTurn = true;
	PlayerWon = false;
}

void BattleSystem::Debugging()
{
	cout << "/*****************************************/" << endl;
	for (size_t i = 0; i < PlayerTroops.size(); i++)
	{
		cout << "Player Troop " << i << " : " << PlayerTroops.at(i)->GetName() << endl;
		cout << "Health : " << PlayerTroops.at(i)->GetHealth() << endl;
		cout << "Stunned : " << PlayerTroops.at(i)->GetStunned() << endl;
		cout << "Bleed : " << PlayerTroops.at(i)->GetBleeding() << endl;
		//cout << ""
	}

	for (size_t i = 0; i < AITroops.size(); i++)
	{
		cout << "Enemy Troop " << i << " : " << AITroops.at(i)->GetName() << endl;
		cout << "Health : " << AITroops.at(i)->GetHealth() << endl;
	}

	cout << "/*****************************************/" << endl;
}