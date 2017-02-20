#ifndef SKILL_H_
#define SKILL_H_
#include <string>
#include "CharacterEntity.h"
using std::string;

// Revised skill codes here, will replace the Old Skill with the New Skill
class Ability
{
public:
	__readonly string name;
	__readonly int id, actioncost, timer, cooldown;
	__readonly float multiplier;
	__readonly STATUSEFFECTS statuseffect;
	__readonly int shiftposition = 0;
	Ability();
	~Ability(){};
	virtual void ApplyAbility(CharacterEntity* Character, CharacterEntity* target	);
};

/************************************************/
/*               Warrior Skills                 */
class Bash : public Ability
{
public:
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
		target->ApplyEffect(statuseffect, Math::RandIntMinMax(1, timer));
	}

};
class Rush : public Ability
{
public:
	Rush();
	~Rush(){};
	virtual void ApplyAbility(CharacterEntity* Character, CharacterEntity* target)
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

class Taunt : public Ability
{
public:
	Taunt();
	~Taunt(){};
	virtual void ApplyAbility(CharacterEntity* Character)
	{
		Character->ApplyEffect(statuseffect, timer);
	}
};

class Stab : public Ability
{
public:
	Stab();
	~Stab(){};
	virtual void ApplyAbility(CharacterEntity* Character, CharacterEntity* target)
	{
		target->ApplyEffect(statuseffect, timer);
	}
};

class DivineE : public Ability
{
public:
	DivineE();
	~DivineE(){};
	virtual void ApplyAbility(CharacterEntity* Character, CharacterEntity* target)
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

/************************************************/
/*                Mage Skills                   */
class MagicB : public Ability
{
public:
	MagicB();
	~MagicB(){};
	virtual void ApplyAbility(CharacterEntity* Character, CharacterEntity* target)
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

class BFlash : public Ability
{
public:
	BFlash();
	~BFlash(){};
	virtual void ApplyAbility(CharacterEntity* Character, CharacterEntity* target)
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
		target->ApplyEffect(statuseffect, timer);
	}
};

class UnholyI : public Ability
{
public:
	UnholyI();
	~UnholyI(){};
	virtual void ApplyAbility(CharacterEntity* Character, CharacterEntity* target)
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
		target->ApplyEffect(statuseffect, timer);
	}

};

class MiasmicC : public Ability
{
public:
	MiasmicC();
	~MiasmicC(){};
	virtual void ApplyAbility(CharacterEntity* Character, CharacterEntity* target)
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
		target->ApplyEffect(statuseffect, timer);
	}
};

class Ars : public Ability
{
public:
	__readonly STATUSEFFECTS statuseffect2;
	Ars();
	~Ars(){};
	virtual void ApplyAbility(CharacterEntity* Character, CharacterEntity* target)
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
		target->ApplyEffect(statuseffect, timer);
		target->ApplyEffect(statuseffect2, timer);
	}
};

class Heal : public Ability
{
public:
	Heal();
	~Heal(){};
	virtual void ApplyAbility(CharacterEntity* Character, CharacterEntity* target)
	{
		int Damage;
		Damage = Character->GetAttack();
		Damage = Damage *= multiplier;
		int Health = target->GetHealth();
		Health += Damage;
		if (Health > target->GetMaxHealth())
		{
			Health = target->GetMaxHealth();
		}
		target->SetHealth(Health);
	}
};

class Esuna : public Ability
{
public:
	Esuna();
	~Esuna(){};
	virtual void ApplyAbility(CharacterEntity* Character, CharacterEntity* target)
	{
		
	}
};

class UnholyG : public Ability
{
public:
	UnholyG();
	~UnholyG(){};
	virtual void ApplyAbility(CharacterEntity* Character, CharacterEntity* target)
	{
		int Damage;
		Damage = Character->GetAttack();
		Damage = Damage *= multiplier;
		int Health = target->GetHealth();
		Health += Damage;
		if (Health > target->GetMaxHealth())
		{
			Health = target->GetMaxHealth();
		}
		target->SetHealth(Health);
	}
};

class DivineG : public Ability
{
public:
	DivineG();
	~DivineG(){};
	virtual void ApplyAbility(CharacterEntity* Character, CharacterEntity* target)
	{
		target->ApplyEffect(statuseffect, timer);
	}
};

class GuardianA : public Ability
{
public:
	GuardianA();
	~GuardianA(){};
	virtual void ApplyAbility(CharacterEntity* Character, CharacterEntity* target)
	{
		target->ApplyEffect(statuseffect, timer);
	}
};

#endif