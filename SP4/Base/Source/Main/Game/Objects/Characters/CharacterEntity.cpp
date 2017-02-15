#include "CharacterEntity.h"



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

void CharacterEntity::SetDamageMitigation()
{
	this->Damagemitigation = (this->Defense) / ((this->Defense) + 1);
}

void CharacterEntity::Init()
{

}

