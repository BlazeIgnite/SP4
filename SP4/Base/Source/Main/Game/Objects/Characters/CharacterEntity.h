#ifndef CHARACTER_ENTITY_H
#define CHARACTER_ENTITY_H

#include "../../Base/Source/Main/Engine/Objects/BaseObject.h"
#include <vector>
#include <string>
#include "CharacterDatabase.h"

using std::string;
using std::vector;

class CharacterEntity : public BaseObject 
{
protected:

private:
	//Character's Base stats

	Vector3 Position;
	Vector3 Scale;
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

	int ID;

	//Final stats
	float DamageMitigation;

	bool Defeated;
	enum CurrentEffect
	{
		isStunned = 1,
		isBleed,
		isDebuff,
		isBuff,
		noeffect,
	};
protected:
	CurrentEffect stunned = noeffect, bleeding = noeffect, buffed = noeffect, debuffed = noeffect;
	int stuntimer, bleedtimer, debufftimer, bufftimer;

public:
	CharacterEntity();
	~CharacterEntity();

	//Getters
	int GetLevel() { return Level; }
	float GetHealth() { return Health; }
	float GetMaxHealth(){ return MaxHealth; }
	int GetAbilityPoints(){ return AbilityPoints; }
	int GetMaxAbilityPoints(){ return MaxAbilityPoints; }
	float GetAttack(){ return Attack; }
	float GetDefense(){ return Defense; }
	float GetMagic(){ return Magic; }
	float GetLuck(){ return Luck; }
	bool GetDefeated() { return Defeated; }
	Vector3 GetVectorPosition(){ return Position; }
	Vector3 GetScale(){ return Scale; }

	//Setters
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
	void SetVectorPosition(Vector3 Position){ this->Position = Position; }
	void SetScale(Vector3 Scale){ this->Scale = Scale; }

	virtual void Levelup(){};

	//This sets the Damage Mitigation for every level
	void SetDamageMitigation();
	float GetDamageMitigation(){ return DamageMitigation; }

	void Init(Vector3 Position);
	virtual void Init(int Level);
	void Update(double dt);
	void ApplyEffect(STATUSEFFECTS statuseffect, int timer);

	string Name;

};

#endif