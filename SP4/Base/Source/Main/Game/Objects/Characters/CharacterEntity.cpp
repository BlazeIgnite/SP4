#include "CharacterEntity.h"
#include "Skill.h"
#include "../../Game/Mains/Application.h"


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

}