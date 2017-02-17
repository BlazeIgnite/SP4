#include "CharacterEntity.h"
#include "Skill.h"
#include "../../Game/Mains/Application.h"


CharacterEntity::CharacterEntity() : Name(""), Level(0), Health(0)
, MaxHealth(0), AbilityPoints(0), MaxAbilityPoints(0), Attack(0), Defense(0)
, Magic(0), Luck(0), DamageMitigation(0), Defeated(false), ID(0)
, stuntimer(0), bleedtimer(0), bufftimer(0), debufftimer(0)
{
}

CharacterEntity::~CharacterEntity()
{
}

void CharacterEntity::SetLevel(int Level)
{
	this->Level = Level;
}
void CharacterEntity::SetHealth(float Health)
{
	this->Health = Health;
}
void CharacterEntity::SetMaxHealth(float MaxHealth)
{ 
	this->MaxHealth = MaxHealth;
}
void CharacterEntity::SetAbilityPoints(int AbilityPoints)
{
	this->AbilityPoints = AbilityPoints;
}
void CharacterEntity::SetMaxAbilityPoints(int MaxAbilityPoints)
{
	this->MaxAbilityPoints = MaxAbilityPoints;
}
void CharacterEntity::SetAttack(float Attack)
{
	this->Attack = Attack;
}
void CharacterEntity::SetDefense(float Defense)
{
	this->Defense = Defense;
}
void CharacterEntity::SetMagic(float Magic)
{
	this->Magic = Magic;
}
void CharacterEntity::SetLuck(float Luck)
{
	this->Luck = Luck;
}
void CharacterEntity::SetDefeated(bool newDefeated)
{
	this->Defeated = newDefeated;
}

void CharacterEntity::SetDamageMitigation()
{
	this->DamageMitigation =(0.06 * Defense) / (1 + 0.06*this->Defense);
}

void CharacterEntity::Init(int Level)
{
	SetDamageMitigation();
}


void CharacterEntity::Init(const Vector3 Position)
{
	this->Position = Position;
}

void CharacterEntity::Update(double dt)
{

}

void CharacterEntity::ApplyEffect(STATUSEFFECTS statuseffect, int timer)
{
	switch (statuseffect)
	{
	case Stun:
	{
		stunned = isStunned;
		stuntimer = timer;
		break;
	}
	case Bleed:
	{
		bleeding = isBleed;
		bleedtimer = timer;
		break;
	}
	case Debuff:
	{
		debuffed = isDebuff;
		debufftimer = timer;
		break;
	}
	case Buff:
	{
		buffed = isBuff;
		bufftimer = timer;
		break;
	}
	default:
		break;
	}
}