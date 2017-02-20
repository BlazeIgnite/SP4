#ifndef CHARACTER_ENTITY_H
#define CHARACTER_ENTITY_H

#include <vector>
#include <string>
#include "../../Base/Source/Main/Engine/Objects/BaseObject.h"
#include "../../Objects/Characters/Skill.h"

using std::string;
using std::vector;

class CharacterEntity : public BaseObject
{
protected:
	//Character's Base stats
	Vector3 Position;
	Vector3 Scale;
	vector<Skill*> SkillList;
	string Name;
	size_t Level;
	size_t Health;
	size_t MaxHealth;
	size_t Attack;
	size_t BattleAttack;
	size_t Defense;
	size_t StunTimer, BleedTimer, DebuffTimer, BuffTimer;
	
	//Base Stats End here
	float ExperiencePoints;
	float NormalAttackmultiplier;
	int DamageMitigation;
	bool Defeated;
	bool Stunned, Bleeding, Buffed, Debuffed;

public:
	CharacterEntity();
	~CharacterEntity();

	//Getters
	inline Vector3 GetVectorPosition(){ return Position; };
	inline Vector3 GetScale(){ return Scale; };
	inline string GetName(){ return Name; };
	inline size_t GetLevel() { return Level; };
	inline size_t GetHealth() { return Health; };
	inline size_t GetMaxHealth(){ return MaxHealth; };
	inline size_t GetAttack(){ return Attack; };
	inline size_t GetBattleAttack(){ return BattleAttack; };
	inline size_t GetDefense(){ return Defense; };
	inline size_t GetStunTimer(){ return StunTimer; };
	inline size_t GetBleedTimer(){ return BleedTimer; };
	inline size_t GetDebuffTimer(){ return DebuffTimer; };
	inline size_t GetBuffTimer(){ return BuffTimer; };
	inline bool GetDefeated(){ return Defeated; };
	inline bool GetStunned(){ return Stunned;	};
	inline bool GetBleeding(){ return Bleeding; };
	inline bool GetBuffed(){ return Buffed; }
	inline bool GetDebuffed(){ return Debuffed; };

	//Setters
	inline void SetPosition(Vector3 Position){ this->Position = Position; };
	inline void SetScale(Vector3 Scale){ this->Scale = Scale; };
	inline void SetName(string Name){ this->Name = Name; };
	inline void SetLevel(size_t Level){ this->Level = Level; };
	inline void SetHealth(size_t Health){ this->Health = Health; };
	inline void SetMaxHealth(size_t MaxHealth){ this->MaxHealth = MaxHealth; };
	inline void SetAttack(size_t Attack){ this->Attack = Attack; };
	inline void SetBattleAttack(size_t BattleAttack) { this->BattleAttack = BattleAttack; };
	inline void SetDefense(size_t Defense){	this->Defense = Defense; };
	inline void SetStunTimer(size_t StunTimer){ this->StunTimer = StunTimer; };
	inline void SetBleedTimer(size_t BleedTimer){ this->BleedTimer = BleedTimer; };
	inline void SetDebuffTimer(size_t DebuffTimer){ this->DebuffTimer = DebuffTimer; };
	inline void SetBuffTimer(size_t BuffTimer){ this->BuffTimer = BuffTimer; };
	inline void SetDefeated(bool Defeated){ this->Defeated = Defeated; };
	inline void SetStunned(bool Stunned){ this->Stunned = Stunned; };
	inline void SetBleeding(bool Bleeding){ this->Bleeding = Bleeding; };
	inline void SetBuffed(bool Buffed){ this->Buffed = Buffed; };
	inline void SetDebuffed(bool Debuffed){ this->Debuffed = Debuffed; };

	virtual void LevelUp() = 0;

	//This sets the Damage Mitigation for every level
	void SetDamageMitigation();
	int GetDamageMitigation(){ return DamageMitigation; }

	virtual void Init(int Level = 1);
	void Update(double dt);
	void ExecuteAttack(CharacterEntity* Target);
//	map<string, Ability> Abilities;
};

#endif