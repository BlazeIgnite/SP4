#include "CharacterEntity.h"
#include "Skill.h"
#include "../../Game/Mains/Application.h"
#include "../../Base/Source/Main/Engine/System/InputManager.h"

CharacterEntity::CharacterEntity() 
: Position(Vector3(0, 0, 0))
, Scale(Vector3(10, 10, 1))
, Name("")
, Level(0)
, Health(0)
, MaxHealth(0)
, Attack(0)
, Defence(0)
, StunTimer(0)
, BleedTimer(0)
, DebuffTimer(0)
, BuffTimer(0)
, DamageMitigation(0)
, ExperiencePoints(0)
, Defeated(false)
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
	SkillList.clear();
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
	this->DamageMitigation = (0.06 * Defence) / (1 + 0.06 * Defence);
}

void CharacterEntity::Init(int Level)
{
	SetDamageMitigation();
}

void CharacterEntity::Update(double dt)
{
	isitHover();
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

bool CharacterEntity::isitHover()
{
	float worldX = InputManager::Instance().GetMousePosition().x;
	float worldY = InputManager::Instance().GetMousePosition().y;

	if (worldY > (GetVectorPosition().y - GetScale().y * 0.5) && worldY < (GetVectorPosition().y + GetScale().y * 0.5))
	{
		if (worldX >(GetVectorPosition().x - GetScale().x * 0.5) && worldX < (GetVectorPosition().x + GetScale().x * 0.5))
			return true;
		else
			return false;
	}
	else
		return false;
}

bool CharacterEntity::GetisPressed()
{
	return isPressed;
}

bool CharacterEntity::GetisSelected()
{
	return isSelected;
}

void CharacterEntity::SetisPressed(bool pressed)
{
	this->isPressed = pressed;
}

void CharacterEntity::SetisSelected(bool select)
{
	this->isSelected = select;
}