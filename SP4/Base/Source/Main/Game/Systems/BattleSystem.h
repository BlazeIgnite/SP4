#ifndef BATTLE_SYSTEM_H
#define BATTLE_SYSTEM_H

#include <map>
#include "../Internal/SingletonTemplate.h"
#include "../AI/AIBase.h"
#include "../Objects/Characters/CharacterEntity.h"
#include "../Objects/Characters/Player.h"

using std::map;

class BattleSystem : public SingletonTemplate<BattleSystem>
{
	map<size_t, CharacterEntity*> PlayerTroops;
	map<size_t, CharacterEntity*> AITroops;
	
	CharacterEntity* SelectedTroop;

	size_t TurnCost;
	bool PlayerTurn;
	bool PlayerWon;
public:
	BattleSystem();
	~BattleSystem();

	// Initialising
	void Init();

	// Setters
	void SetPlayerTroops(size_t position, CharacterEntity* Troop);
	void SetAITroops(size_t position, CharacterEntity* Troop);
	void SetPlayerTurn(bool newPlayerTurn);
	inline void SetSelectedTroop(CharacterEntity* newSelectedTroop){ SelectedTroop = newSelectedTroop; };
	inline void SetTurnCost(size_t newTurnCost) { TurnCost = newTurnCost; };
	inline void SetPlayerWon(bool newPlayerWon) { PlayerWon = newPlayerWon; };
	 
	 // Getters
	inline map<size_t, CharacterEntity*>& GetPlayerTroops() { return PlayerTroops; };
	inline map<size_t, CharacterEntity*>& GetAITroops() { return AITroops; };
	inline CharacterEntity* GetPlayerTroopAttacking(size_t position) { return PlayerTroops.find(position)->second; };
	inline CharacterEntity* GetAITroopAttacking(size_t position) { return AITroops.find(position)->second; };
	inline CharacterEntity* GetSelectedTroop() { return SelectedTroop; };
	inline size_t GetTurnCost(){ return TurnCost; };
	inline bool GetPlayerTurn(){ return PlayerTurn; };
	inline bool GetPlayerWon(){ return PlayerWon; };

	bool CanActivateSkill();

	// Switching Spots
	void SwitchSpots(map<size_t, CharacterEntity*>& TroopMap, size_t FirstPosition, size_t SecondPosition);
	void MoveTroopBackByOne(map<size_t, CharacterEntity*>& TroopMap);
	void MoveTroopBackByTwo(map<size_t, CharacterEntity*>& TroopMap);
	void MoveTroopFrontByOne(map<size_t, CharacterEntity*>& TroopMap);
	void MoveTroopFrontByTwo(map<size_t, CharacterEntity*>& TroopMap);

	// Damage Calculations all here
	void DamageCalculation(CharacterEntity* Attacker, size_t target);
	void DamageCalculation(CharacterEntity* Attacker, size_t target, Skill* AttackerSkill);
	void ApplyFriendlyEffect(map<size_t, CharacterEntity*>& TeamMap, CharacterEntity* User, size_t TargettedTeammate);
	// Status Effect Calculations all here
	void SetStatusEffect(map<size_t, CharacterEntity*>& TeamMap, size_t target);

	void Reset();

};

#endif