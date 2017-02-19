#ifndef CHARACTER_ENTITY_H
#define CHARACTER_ENTITY_H

#include "../../Base/Source/Main/Engine/Objects/BaseObject.h"
#include <vector>
#include <string>
#include <map>
#include "CharacterDatabase.h"

using std::string;
using std::vector;
using std::map;
class Ability;

class CharacterEntity : public BaseObject 
{
	//Character's Base stats
	// Can this be in a bool? you are using up 4 bytes for each enum value as compared to 1 byte (bool).
	enum CurrentEffect
	{
		isStunned = 1,
		isBleed,
		isDebuff,
		isBuff,
		noeffect,
	};

	Vector3 Position;
	Vector3 Scale;
	string Name;
	int	Level;
	int AbilityPoints;
	int MaxAbilityPoints;
	float Health;
	float MaxHealth;
	float Attack;
	float Defense;
	float Magic;
	float Luck;
	//Base Stats End here

	//Final stats
	float DamageMitigation;
	bool Defeated;
protected:
	Ability *skill;
	CurrentEffect stunned = noeffect, bleeding = noeffect, buffed = noeffect, debuffed = noeffect;
	int stuntimer, bleedtimer, debufftimer, bufftimer;

public:
	CharacterEntity();
	~CharacterEntity();

	//Getters
	Vector3 GetVectorPosition(){ return Position; }
	Vector3 GetScale(){ return Scale; }
	string GetName(){ return Name; }
	int GetLevel() { return Level; }
	int GetAbilityPoints(){ return AbilityPoints; }
	int GetMaxAbilityPoints(){ return MaxAbilityPoints; }
	float GetHealth() { return Health; }
	float GetMaxHealth(){ return MaxHealth; }
	float GetAttack(){ return Attack; }
	float GetDefense(){ return Defense; }
	float GetMagic(){ return Magic; }
	float GetLuck(){ return Luck; }
	bool GetDefeated() { return Defeated; }
	Ability* Getskill(){ return skill; }

	//Setters
	void SetVectorPosition(Vector3 Position){ this->Position = Position; }
	void SetScale(Vector3 Scale){ this->Scale = Scale; }
	void SetName(string Name){ this->Name = Name; }
	void SetLevel(int Level);
	void SetHealth(float Health);
	void SetMaxHealth(float MaxHealth);
	void SetAbilityPoints(int AbilityPoints);
	void SetMaxAbilityPoints(int MaxAbilityPoints);
	void SetAttack(float Attack);
	void SetDefense(float Defense);
	void SetMagic(float Magic);
	void SetLuck(float Luck);
	void SetDefeated(bool Defeated);

	virtual void Levelup(){};

	//This sets the Damage Mitigation for every level
	void SetDamageMitigation();
	float GetDamageMitigation(){ return DamageMitigation; }

	void Init(Vector3 Position);
	virtual void Init(int Level);
	void Update(double dt);
	void ApplyEffect(STATUSEFFECTS statuseffect, int timer);

//	map<string, Ability> Abilities;
};

#endif