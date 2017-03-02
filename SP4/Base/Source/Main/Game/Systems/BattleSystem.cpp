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
	
	if (PlayerTroops.size() != 0)
		PlayerTroops.clear();
	if (PlayerTroopSkills.size() != 0)
		PlayerTroopSkills.clear();
	if (AITroops.size() != 0)
		AITroops.clear();

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
		EmptySkillMap[EmptySkillMap.size()] = (*SkillIt);
		PlayerTroopSkills[playerPosition] = EmptySkillMap;
	}
	else
	{
		int SkillPosition = PlayerTroopSkills.find(playerPosition)->second.size();
		map<size_t, Skill*>::iterator itr2 = itr->second.find(SkillPosition);
		if (itr2 == itr->second.end())
			PlayerTroopSkills.find(playerPosition)->second[SkillPosition] = (*SkillIt);
		else
			PlayerTroopSkills.find(playerPosition)->second.at(SkillPosition) = (*SkillIt);
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

void BattleSystem::CheckTroopPositions()
{
	map<size_t, CharacterEntity*>::iterator it = PlayerTroops.find(0);
	map<size_t, CharacterEntity*>::iterator it1 = PlayerTroops.find(1);
	map<size_t, CharacterEntity*>::iterator it2 = PlayerTroops.find(2);

	if (it == PlayerTroops.end())
	{
		if (it1 != PlayerTroops.end())
		{
			CharacterEntity* temp = it1->second;
			map<size_t, Skill*> ChangingMap = PlayerTroopSkills[1];
			
			PlayerTroopSkills[0] = ChangingMap;

			SetPlayerTroops(0, temp);

			// Bye bye
			PlayerTroops.erase(1);
			PlayerTroopSkills.erase(1);

			if (it2 != PlayerTroops.end())
			{
				CharacterEntity* tempo = it2->second;
				map<size_t, Skill*> ChangingMap2 = PlayerTroopSkills[2];

				PlayerTroopSkills[1] = ChangingMap2;

				SetPlayerTroops(1, tempo);

				// Bye Bye
				PlayerTroops.erase(2);
				PlayerTroopSkills.erase(2);
			}
			return;
		}
		if (it2 != PlayerTroops.end())
		{
			CharacterEntity* tempo = it2->second;
			map<size_t, Skill*> ChangingMap2 = PlayerTroopSkills[2];

			PlayerTroopSkills[0] = ChangingMap2;

			SetPlayerTroops(0, tempo);

			// Bye Bye
			PlayerTroops.erase(2);
			PlayerTroopSkills.erase(2);
		}
	}
	else if (it1 == PlayerTroops.end())
	{
		if (it2 != PlayerTroops.end())
		{
			CharacterEntity* temp = it2->second;
			map<size_t, Skill*> ChangingMap2 = PlayerTroopSkills[2];

			PlayerTroopSkills[1] = ChangingMap2;

			SetPlayerTroops(1, temp);
			
			// Bye Bye
			PlayerTroops.erase(2);
			PlayerTroopSkills.erase(2);
		}
	}
	//if (PlayerTroops[0] == nullptr)
	//{
	//	if (PlayerTroops[1] != nullptr)
	//	{
	//		//	MoveTroopFrontByOne(PlayerTroops);
	//		CharacterEntity* temp = PlayerTroops[1];
	//		SetPlayerTroops(0, temp);
	//		PlayerTroops[1]->SetPosition(Vector3(0, 0, 0));
	//		PlayerTroops[1] = NULL;
	//		if (PlayerTroops[2] != nullptr)
	//		{
	//			CharacterEntity* temp2 = PlayerTroops[2];
	//			SetPlayerTroops(1, temp2);
	//			PlayerTroops[2]->SetPosition(Vector3(0, 0, 0));
	//			PlayerTroops[2] = NULL;
	//		}
	//	}
	//	else //if (PlayerTroops[2] != nullptr)
	//	{
	//		//	MoveTroopFrontByTwo(PlayerTroops);
	//		CharacterEntity* temp = PlayerTroops[2];
	//		SetPlayerTroops(1, temp);
	//		PlayerTroops[2]->SetPosition(Vector3(0, 0, 0));
	//		PlayerTroops[2] = NULL;
	//	}
	//	return;
	//}
	//else //if (PlayerTroops[1] == nullptr)
	//{
	//	if (PlayerTroops[2] != nullptr)
	//	{
	//		//	MoveTroopFrontByOne(PlayerTroops);
	//		CharacterEntity* temp = PlayerTroops[2];
	//		SetPlayerTroops(1, temp);
	//		PlayerTroops[2]->SetPosition(Vector3(0, 0, 0));
	//		PlayerTroops[2] = NULL;
	//	}
	//}
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

size_t BattleSystem::GetSelectedEnemyTroopPosition()
{
	for (map<size_t, CharacterEntity*>::iterator it = AITroops.begin(); it != AITroops.end(); it++)
	{
		if (it->second == SelectedEnemyTroop)
			return it->first;
	}
	return NULL;
}

CharacterEntity* BattleSystem::GetPlayerTroopAttacking(size_t position)
{
	if (position >= PlayerTroops.size())
		return NULL;
	return PlayerTroops.at(position);
}

//Skill* BattleSystem::GetSelectedSkill(size_t position)
//{
//	if (position >= PlayerTroopSkills.size())
//		return NULL;
//	return PlayerTroopSkills.at(GetSelectedTroopPosition()).at(position);
//}
Skill* BattleSystem::GetSelectedSkill(size_t position)
{
	if (position >= PlayerTroopSkills.at(GetSelectedTroopPosition()).size())
		return NULL;
	map<size_t, Skill*> t =  PlayerTroopSkills.at(GetSelectedTroopPosition());
	return PlayerTroopSkills.at(GetSelectedTroopPosition()).at(position);
}

void BattleSystem::SetPlayerTurn(bool newPlayerTurn)
{
	TurnCost = 100;
	SelectedTroop = NULL;
	SelectedEnemyTroop = NULL;
	SelectedSkill = NULL;

	if (PlayerTurn)
	{
		if (GetNumberOfAITroopAlive() >= 1 && AITroops[0]->GetDefeated())
		{
			MoveTroopFrontByOne(AITroops);
			if (AITroops[0]->GetDefeated())
				MoveTroopFrontByOne(AITroops);
		}
		if (GetNumberOfAITroopAlive() == 2 && AITroops[1]->GetDefeated())
		{
			SwitchSpots(AITroops, 1, 2);
		}
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
		if (GetNumberOfPlayerTroopAlive() >= 1 && PlayerTroops[0]->GetDefeated())
		{
			MoveTroopFrontByOne(PlayerTroops);
			if (PlayerTroops[0]->GetDefeated())
				MoveTroopFrontByOne(PlayerTroops);
		}
		if (GetNumberOfPlayerTroopAlive() == 2 && PlayerTroops[1]->GetDefeated())
		{
			SwitchSpots(PlayerTroops, 1, 2);
		}
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

	if (TroopMap == PlayerTroops)
	{
		map<size_t, Skill*> tempMap = PlayerTroopSkills.at(FirstPosition);
		PlayerTroopSkills[FirstPosition] = PlayerTroopSkills[SecondPosition];
		PlayerTroopSkills[SecondPosition] = tempMap;
	}

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
		int tempdamage = damage - targettroop->GetDefence();
		if (tempdamage <= 0)
			tempdamage = 1;
		int tempHealth = targettroop->GetHealth() - tempdamage;
		if (tempHealth <= 0)
			tempHealth = 0;
		targettroop->SetHealth(tempHealth);
		SetStatusEffect(target, AttackerSkill);
		TurnCost -= AttackerSkill->GetActionCost();
		if (targettroop->GetHealth() == 0)
			targettroop->SetDefeated(true);

		return (size_t)tempdamage;
	}
	else
	{
		CharacterEntity* targettroop = PlayerTroops.find(target)->second;
		int tempdamage = damage - targettroop->GetDefence();
		if (tempdamage <= 0)
			tempdamage = 1;
		int tempHealth = targettroop->GetHealth() - tempdamage;
		if (tempHealth <= 0)
			tempHealth = 0;
		targettroop->SetHealth(tempHealth);
		SetStatusEffect(target, AttackerSkill);
		TurnCost -= AttackerSkill->GetActionCost();
		if (targettroop->GetHealth() == 0)
			targettroop->SetDefeated(true);
		return (size_t)tempdamage;
	}
	return 0;
}

bool BattleSystem::CanActivateSkill(CharacterEntity* Attacker, size_t target, Skill* AttackerSkill)
{
	if (Attacker == NULL || AttackerSkill == NULL)
		return false;
	if (PlayerTurn)
	{
		if (target >= AITroops.size())
			return false;

		if (AITroops.at(target)->GetDefeated())
			return false;

		for (map<size_t, CharacterEntity*>::iterator it = PlayerTroops.begin(); it != PlayerTroops.end(); it++)
		{
			if ((*it).second == Attacker)
			{
				if (!Attacker->GetStunned() && !Attacker->GetDefeated())
				{
					int temp = TurnCost - AttackerSkill->GetActionCost();

					if (temp < 0)
						return false;
					else
					{
						if (AttackerSkill->GetTurnCooldown() == 0)
						{
							if (AttackerSkill->GetRequiredPosition((*it).first))
							{
								if (AttackerSkill->GetSelectableTarget(target))
									return true;
								else
									return false;
							}
							else
								return false;
						}
						else
							return false;
					}
				}
				else
					return false;
			}
		}
		return false;
	}
	else
	{
		if (target >= PlayerTroops.size())
			return false;

		if (PlayerTroops.at(target)->GetDefeated())
			return false;

		for (map<size_t, CharacterEntity*>::iterator it = AITroops.begin(); it != AITroops.end(); it++)
		{
			if ((*it).second == Attacker)
			{
				if (!Attacker->GetStunned() && !Attacker->GetDefeated())
				{
					int temp = TurnCost - AttackerSkill->GetActionCost();

					if (temp < 0)
						return false;
					else
					{
						if (AttackerSkill->GetTurnCooldown() == 0)
						{
							if (AttackerSkill->GetRequiredPosition((*it).first))
							{
								if (AttackerSkill->GetSelectableTarget(target))
									return true;
								else
									return false;
							}
							else
								return false;
						}
						else
							return false;
					}
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
			AITroops.at(target)->SetStunTimer(SkillUsed->GetStatusEffectTimer("Stun"));
			AudioPlayer::Instance().PlayStunEffect();
		}
		if (SkillUsed->StatusEffectExistence("Bleed"))
		{
			AITroops.at(target)->SetBleeding(true);
			AITroops.at(target)->SetBleedTimer(SkillUsed->GetStatusEffectTimer("Bleed"));
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
			PlayerTroops.at(target)->SetStunTimer(SkillUsed->GetStatusEffectTimer("Stun"));
			AudioPlayer::Instance().PlayStunEffect();
		}
		if (SkillUsed->StatusEffectExistence("Bleed"))
		{
			PlayerTroops.at(target)->SetBleeding(true);
			PlayerTroops.at(target)->SetBleedTimer(SkillUsed->GetStatusEffectTimer("Bleed"));
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

void BattleSystem::ClearWave()
{
	SelectedTroop = NULL;
	SelectedEnemyTroop = NULL;
	SelectedSkill = NULL;

	for (auto it : AITroops)
	{
		if (it.second != nullptr)
			delete it.second;
		it.second = nullptr;
	}
	AITroops.clear();

	SetTurnCost(100);
	PlayerTurn = true;
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