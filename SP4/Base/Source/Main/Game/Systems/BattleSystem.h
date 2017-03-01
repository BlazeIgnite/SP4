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
	
	map<size_t, map<size_t, Skill*>> PlayerTroopSkills;

	CharacterEntity* SelectedTroop;
	CharacterEntity* SelectedEnemyTroop;
	Skill* SelectedSkill;

	size_t DisplaySkillNum;
	size_t TurnCost;
	size_t PlayerStatus;
	int PlayerWon;
	bool PlayerTurn;
public:
	BattleSystem();
	~BattleSystem();

	// Initialising
	void Init();

	// Setters
	void SetPlayerTroops(size_t position, CharacterEntity* Troop);
	void SetAITroops(size_t position, CharacterEntity* Troop);
	void SetPlayerTroopSkills(size_t playerPosition, size_t skillPosition);
	void SetPlayerTurn(bool newPlayerTurn);
	void SetSelectedTroop(CharacterEntity* newSelectedTroop);
	inline void SetSelectedEnemyTroop(CharacterEntity* newSelectedEnemyTroop){ SelectedEnemyTroop = newSelectedEnemyTroop; };
	inline void SetSelectedSkill(Skill* newSelectedskill){ SelectedSkill = newSelectedskill; };
	inline void SetDisplaySkillNum(size_t newDisplaySkillNum){ DisplaySkillNum = newDisplaySkillNum; };
	inline void SetTurnCost(size_t newTurnCost) { TurnCost = newTurnCost; };
	inline void SetPlayerWon(int newPlayerWon) { PlayerWon = newPlayerWon; };
	 
	 // Getters
	size_t GetSelectedTroopPosition();
	size_t GetNumberOfAITroopAlive();
	size_t GetNumberOfPlayerTroopAlive();
	size_t GetSelectedEnemyTroopPosition();
	CharacterEntity* GetPlayerTroopAttacking(size_t position);
	Skill* GetSelectedSkill(size_t position);
	inline map<size_t, CharacterEntity*>& GetPlayerTroops() { return PlayerTroops; };
	inline map<size_t, CharacterEntity*>& GetAITroops() { return AITroops; };
	inline map<size_t, Skill*>& GetPlayerTroopSkills(size_t position) { return PlayerTroopSkills.at(position); };
	inline CharacterEntity* GetAITroopAttacking(size_t position) { return AITroops.find(position)->second; };
	inline CharacterEntity* GetSelectedTroop() { return SelectedTroop; };
	inline CharacterEntity* GetSelectedEnemyTroop() { return SelectedEnemyTroop; };
	inline Skill* GetSkillInMap(size_t Character, size_t Skill_Pos) { return PlayerTroopSkills.at(Character).at(Skill_Pos); };
	inline Skill* GetSelectedSkill() { return SelectedSkill; };
	inline size_t GetDisplaySkillNum(){ return DisplaySkillNum; };
	inline size_t GetTurnCost(){ if (TurnCost <= 0) TurnCost = 0; return TurnCost; };
	inline int GetPlayerWon(){ return PlayerWon; };
	inline bool GetPlayerTurn(){ return PlayerTurn; };

	// Use this at every start of scene battles
	void CheckTroopPositions();

	// Switching Spots
	void SwitchSpots(map<size_t, CharacterEntity*>& TroopMap, size_t FirstPosition, size_t SecondPosition);
	void MoveTroopBackByOne(map<size_t, CharacterEntity*>& TroopMap);
	void MoveTroopBackByTwo(map<size_t, CharacterEntity*>& TroopMap);
	void MoveTroopFrontByOne(map<size_t, CharacterEntity*>& TroopMap);
	void MoveTroopFrontByTwo(map<size_t, CharacterEntity*>& TroopMap);

	// Damage Calculations all here
	size_t DamageCalculation(size_t target, Skill* AttackerSkill);
	// Buffing or Healing goes here
	void ApplyFriendlyEffect(size_t TargettedTeammate, Skill* SkillUsed);
	// Status Effect Calculations all here
	void SetStatusEffect(size_t target, Skill* skillUsed);

	// Checking if Skill can be activated
	bool CanActivateSkill(CharacterEntity* Attacker, size_t Target, Skill* AttackerSkill);
	
	void Reset();

	void ClearWave();

	void Debugging();
};

#endif