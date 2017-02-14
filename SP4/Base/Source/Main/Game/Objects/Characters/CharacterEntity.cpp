#include "CharacterEntity.h"



int CharacterEntity::GetLevel()
{
	return Level;
}
float CharacterEntity::GetHealth()
{
	return Health;
}
float CharacterEntity::GetMaxHealth()
{
	return MaxHealth;
}
float CharacterEntity::GetAbilityPoints()
{
	return AbilityPoints;
}
float CharacterEntity::GetMaxAbilityPoints()
{
	return MaxAbilityPoints;
}
float CharacterEntity::GetAttack()
{
	return Attack;
}
float CharacterEntity::GetDefense()
{
	return Defense;
}
float CharacterEntity::GetMagic()
{
	return Magic;
}
float CharacterEntity::GetLuck()
{
	return Luck;
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
void CharacterEntity::SetAbilityPoints(float AbilityPoints)
{
	this->AbilityPoints = AbilityPoints;
}
void CharacterEntity::SetMaxAbilityPoints(float MaxAbilityPoints)
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