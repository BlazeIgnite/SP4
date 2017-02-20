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
	size_t Defense;
	size_t StunTimer, BleedTimer, DebuffTimer, BuffTimer;

	//Base Stats End here
	int DamageMitigation;
	bool Defeated;
	bool Stunned, Bleeding, Buffed, Debuffed;

public:
	CharacterEntity();
	~CharacterEntity();

	//Getters
	Vector3 GetVectorPosition(){ return Position; }
	Vector3 GetScale(){ return Scale; }
	string GetName(){ return Name; }
	size_t GetLevel() { return Level; }
	size_t GetHealth() { return Health; }
	size_t GetMaxHealth(){ return MaxHealth; }
	size_t GetAttack(){ return Attack; }
	size_t GetDefense(){ return Defense; }
	size_t GetStunTimer(){ return StunTimer; }
	size_t GetBleedTimer(){ return BleedTimer; }
	size_t GetDebuffTimer(){ return DebuffTimer; }
	size_t GetBuffTimer(){ return BuffTimer; }
	bool GetDefeated() { return Defeated; }
	bool GetStunned(){ return Stunned; }
	bool GetBleeding(){ return Bleeding; }
	bool GetBuffed(){ return Buffed; }
	bool GetDebuffed(){ return Debuffed; }

	//Setters
	void SetPosition(Vector3 Position);
	void SetScale(Vector3 Scale);
	void SetName(string Name);
	void SetLevel(size_t Level);
	void SetHealth(size_t Health);
	void SetMaxHealth(size_t MaxHealth);
	void SetAttack(size_t Attack);
	void SetDefense(size_t Defense);
	void SetStunTimer(size_t StunTimer);
	void SetBleedTimer(size_t BleedTimer);
	void SetDebuffTimer(size_t DebuffTimer);
	void SetBuffTimer(size_t BuffTimer);
	void SetDefeated(bool Defeated);
	void SetStunned(bool Stunned);
	void SetBleeding(bool Bleeding);
	void SetBuffed(bool Buffed);
	void SetDebuffed(bool Debuffed);

	virtual void LevelUp() = 0;

	//This sets the Damage Mitigation for every level
	void SetDamageMitigation();
	int GetDamageMitigation(){ return DamageMitigation; }

	virtual void Init(int Level);
	void Update(double dt);

//	map<string, Ability> Abilities;
};

#endif