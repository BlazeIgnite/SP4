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
, DamageMitigation(0)
{
	for (size_t i = 0; i < 4; i++)
	{
		StatusEffectTimer[i] = 0;
		StatusEffect[i] = false;
	}
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