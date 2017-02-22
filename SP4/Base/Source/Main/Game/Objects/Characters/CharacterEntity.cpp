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
	for (vector<Skill*>::iterator it = SkillList.begin(); it != SkillList.end(); it++)
	{
		if ((*it) != nullptr)
		{
			delete (*it);
			(*it) = nullptr;
		}
	}
}

Skill* CharacterEntity::GetSkillInVector(string SkillName)
{
	for (vector<Skill*>::iterator it = SkillList.begin(); it != SkillList.end(); it++)
	{
		if ((*it)->GetName() == SkillName)
			return (*it);
	}
	return nullptr;
}

void CharacterEntity::SetDamageMitigation()
{
	this->DamageMitigation = (0.06 * Defense) / (1 + 0.06 * Defense);
}

void CharacterEntity::Init(int Level)
{
	SetDamageMitigation();
}

void CharacterEntity::Update(double dt)
{

}

void CharacterEntity::BleedEffect()
{
	int tempHealth = this->GetHealth();
	tempHealth = tempHealth - (Math::RandIntMinMax(5, 8));
	if (tempHealth <= 1)
	{
		tempHealth = 1;
	}
	this->SetHealth(tempHealth);
}

void CharacterEntity::WhileinBuff()
{

}

void CharacterEntity::WhileinDebuff()
{

}

void CharacterEntity::ResetStats()
{

}