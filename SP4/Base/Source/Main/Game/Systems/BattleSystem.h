#ifndef BATTLE_SYSTEM_H
#define BATTLE_SYSTEM_H

#include "../Internal/SingletonTemplate.h"
#include "../AI/AIBase.h"
#include "../Objects/Characters/CharacterEntity.h"
#include "../Objects/Characters/CharacterDatabase.h"
#include "../Objects/Characters/Player.h"

using std::vector;

class BattleSystem : public SingletonTemplate<BattleSystem>
{
	map<size_t, CharacterEntity*> PlayerTroops;
	map<size_t, CharacterEntity*> AITroops;

	float TurnCost;

	bool PlayerTurn;
public:
	BattleSystem();
	~BattleSystem();

	// Initialising
	void Init();

	// Setters
	void SetPlayerTroops(size_t position, CharacterEntity* Troop);
	void SetAITroops(size_t position, CharacterEntity* Troop);
	void SetTurnCost(float newTurnCost);
	void SetPlayerTurn(bool newPlayerTurn);

	// Getters
	map<size_t, CharacterEntity*> GetPlayerTroops();
	map<size_t, CharacterEntity*> GetAITroops();
	CharacterEntity* GetPlayerTroopAttacking(size_t position);
	CharacterEntity* GetAITroopAttacking(size_t position);
	float GetTurnCost();
	bool GetPlayerTurn();

	// Switching Spots
	void SwitchSpots(map<size_t, CharacterEntity*> TroopMap, size_t FirstPosition, size_t SecondPosition);

	// Damage Calculations all here
	void DamageCalculation(CharacterEntity* Attacker, size_t target);
	void DamageCalculation(CharacterEntity* Attacker, size_t target, Skill AttackerSkill);

	// Status Effect Calculations all here
	void SetStatusEffect(CharacterEntity* Attacker, size_t target);

};

#endif