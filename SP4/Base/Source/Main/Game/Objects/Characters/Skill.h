#ifndef SKILL_H_
#define SKILL_H_
#include <string>
#include "CharacterEntity.h"
using std::string;

// Revised skill codes here, will replace the Old Skill with the New Skill
class Ability
{
public:
	__readonly int shiftposition = 0;
	Ability();
	~Ability(){};
	virtual void ApplyAbility(CharacterEntity* Character, CharacterEntity* target	);
};
class PhysicalAbility : public Ability
{
public:
	__readonly int shiftposition = 0;
	PhysicalAbility(){};
	~PhysicalAbility(){};
	virtual void ApplyAbility(CharacterEntity* Character, CharacterEntity* target)
	{

	}
};
class Bash : public PhysicalAbility
{
public:
	__readonly int shiftposition;
	__readonly string name;
	__readonly int id, abilitycost, actioncost, timer;
	__readonly float multiplier;
	__readonly STATUSEFFECTS statuseffect;
	Bash();
	~Bash(){};
	virtual void ApplyAbility(CharacterEntity* Character,CharacterEntity* target)
	{
		int Damage;
		Damage = Character->GetAttack(); 
		Damage = Damage *= multiplier;
		int Health = target->GetHealth();
		Health -= Damage;
		if (Health < 0)
		{
			Health = 0;
		}
		target->SetHealth(Health);
	}

};
#endif