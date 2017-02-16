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

	void Init();

	// Setters
	void SetPlayerTurn(bool newPlayerTurn);
	void SetTurnCost(float newTurnCost);

	void SetPlayerTroops(size_t position, CharacterEntity* Troop);
	void SetAITroops(size_t position, CharacterEntity* Troop);

	CharacterEntity* GetPlayerTroopAttacking(size_t position);
	CharacterEntity* GetAITroopAttacking(size_t position);
	// Getters
	bool GetPlayerTurn();
	float GetTurnCost();

	// Damage Calculations all here
	void DamageCalculation(CharacterEntity* Attacker, int target);

	// Status Effect Calculations all here
	void SetStatusEffect(CharacterEntity* Attacker, int target);

};

#endif