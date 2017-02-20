#include "CharacterEntity.h"
#include "Skill.h"
#include "../../Game/Mains/Application.h"


<<<<<<< HEAD
CharacterEntity::CharacterEntity() : Name(""), Level(0), Health(0)
, MaxHealth(0), AbilityPoints(0), MaxAbilityPoints(0), Attack(0), Defense(0)
, Magic(0), Luck(0), DamageMitigation(0), Defeated(false), ID(0)
, stuntimer(0), bleedtimer(0), bufftimer(0), debufftimer(0), NormalAttackmultiplier(0.00f)
=======
CharacterEntity::CharacterEntity() 
: Position(Vector3(0, 0, 0))
, Scale(Vector3(1, 1, 1))
, Name("")
, Level(0)
, Health(0)
, MaxHealth(0)
, Attack(0)
, BattleAttack(0)
, Defense(0)
, StunTimer(0)
, BleedTimer(0)
, DebuffTimer(0)
, BuffTimer(0)
, DamageMitigation(0)
, Defeated(false)
, Stunned(false)
, Bleeding(false)
, Buffed(false)
, Debuffed(false)
>>>>>>> f00a5bc837d4201a0b4fc74129ca89c7bd4d5169
{
}

CharacterEntity::~CharacterEntity()
{
}

void CharacterEntity::SetPosition(Vector3 Position)
{
	this->Position = Position;
}
void CharacterEntity::SetScale(Vector3 Scale)
{
	this->Scale = Scale;
}
void CharacterEntity::SetLevel(size_t Level)
{
	this->Level = Level;
}
void CharacterEntity::SetHealth(size_t Health)
{
	this->Health = Health;
}
void CharacterEntity::SetMaxHealth(size_t MaxHealth)
{ 
	this->MaxHealth = MaxHealth;
}
void CharacterEntity::SetAttack(size_t Attack)
{
	this->Attack = Attack;
}
void CharacterEntity::SetBattleAttack(size_t BattleAttack)
{
	this->BattleAttack = BattleAttack;
}
void CharacterEntity::SetDefense(size_t Defense)
{
	this->Defense = Defense;
}
void CharacterEntity::SetDefeated(bool newDefeated)
{
	this->Defeated = newDefeated;
}

void CharacterEntity::SetDamageMitigation()
{
	this->DamageMitigation =(0.06 * Defense) / (1 + 0.06 * Defense);
}

void CharacterEntity::Init(int Level)
{
	SetDamageMitigation();
}

void CharacterEntity::Update(double dt)
{

<<<<<<< HEAD
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

void CharacterEntity::ExecuteAttack(CharacterEntity* Target)
{
	int Damage = GetAttack();
	Damage *= NormalAttackmultiplier;
	Damage = static_cast<int>(Damage);

	int temphealth = Target->GetHealth();
	temphealth -= Damage;
	if (temphealth <= 0)
	{
		temphealth = 0;
	}
	Target->SetHealth(temphealth);
=======
>>>>>>> f00a5bc837d4201a0b4fc74129ca89c7bd4d5169
}