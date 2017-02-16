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

	// Getters
	bool GetPlayerTurn();
	float GetTurnCost();

	void SetStatusEffect(CharacterEntity* Attacker, Target target);
	void DamageCalculation(CharacterEntity* Attacker, Target target);

};

#endif