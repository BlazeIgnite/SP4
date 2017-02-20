#include "Skill.h"
//#include "CharacterDatabase.h"

/************************************************/
/*                   Skills                     */
//Skill::Skill() : shiftposition(0)
//{
//
//}
//
//Skill::~Skill()
//{
//
//}
//
//float Skill::SkillBehavior()
//{
//	return 0;
//}


/************************************************/
/*               Revised Skills                 */
/************************************************/

Skill::Skill()
: Name("")
, StatusEffect("")
, StatusEffectTimer(0)
, Damage(0)
, Heal(0)
, ShiftPosition(0)
, ActionCost(0)
, TurnCooldown(0)
, MaxTurnCooldown(0)
{
	bool temp = false;
	for (int i = 0; i < 3; i++)
	{
		RequiredPosition.push_back(temp);
		SelectableTarget.push_back(temp);
	}
}

Skill::~Skill()
{}

// Setters
void Skill::SetName(string newName)
{
	Name = newName;
}
void Skill::SetDamage(size_t newDamage)
{
	Damage = newDamage;
}
void Skill::SetHeal(size_t newHeal)
{
	Heal = newHeal;
}
void Skill::SetShiftPosition(size_t newShiftPosition)
{
	ShiftPosition = newShiftPosition;
}
void Skill::SetActionCost(size_t newActionCost)
{
	ActionCost = newActionCost;
}
void Skill::SetTurnCooldown(size_t newTurnCooldown)
{
	TurnCooldown = newTurnCooldown;
}
void Skill::SetMaxTurnCooldown(size_t newMaxTurnCooldown)
{
	MaxTurnCooldown = newMaxTurnCooldown;
}
void Skill::SetRequiredPosition(size_t position, bool newRequiredPosition)
{
	RequiredPosition[position] = newRequiredPosition;
}
void Skill::SetSelectableTarget(size_t position, bool newSelectableTarget)
{
	SelectableTarget[position] = newSelectableTarget;
}

// Getters
string Skill::GetName()
{
	return Name;
}
size_t Skill::GetDamage()
{
	return Damage;
}
size_t Skill::GetHeal()
{
	return Heal;
}
size_t Skill::GetShiftPosition()
{
	return ShiftPosition;
}
size_t Skill::GetActionCost()
{
	return ActionCost;
}
size_t Skill::GetTurnCooldown()
{
	return TurnCooldown;
}
size_t Skill::GetMaxTurnCooldown()
{
	return MaxTurnCooldown;
}
bool Skill::GetRequiredPosition(size_t position)
{
	for (vector<bool>::iterator it = RequiredPosition.begin(); it != RequiredPosition.end(); it++)
	{
		if ((*it) == position)
			return (*it);
	}
}
bool Skill::GetSelectableTarget(size_t position)
{
	for (vector<bool>::iterator it = SelectableTarget.begin(); it != SelectableTarget.end(); it++)
	{
		if ((*it) == position)
			return (*it);
	}
}