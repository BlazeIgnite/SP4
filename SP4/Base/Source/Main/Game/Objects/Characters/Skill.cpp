#include "Skill.h"

/************************************************/
/*               Revised Skills                 */
/************************************************/

Skill::Skill()
: Name("")
, Damage(0)
, Heal(0)
, ShiftPosition(0)
, ActionCost(0)
, TurnCooldown(0)
, MaxTurnCooldown(0)
{
	for (int i = 0; i < 3; i++)
	{
		RequiredPosition[i] = false;
		SelectableTarget[i] = false;
	}
}

Skill::~Skill()
{}

// Setters
void Skill::SetStatusEffect(size_t StatusEffectTimer, string newStatusEffect)
{
	std::map<size_t, vector<string>>::iterator itr = StatusEffect.find(StatusEffectTimer);
	if (itr == StatusEffect.end())
	{
		vector<string> EmptyVector;
		EmptyVector.push_back(newStatusEffect);
		StatusEffect[StatusEffectTimer] = EmptyVector;
	}
	else
		StatusEffect.find(StatusEffectTimer)->second.push_back(newStatusEffect);
}

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
map<size_t, vector<string>> Skill::GetStringStatusEffect()
{
	return StatusEffect;
}
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
	for (size_t i = 0; i < 3; i++)
	{
		if (i == position)
			return RequiredPosition[i];
	}
	return false;
}
bool Skill::GetSelectableTarget(size_t position)
{
	for (size_t i = 0; i < 3; i++)
	{
		if (i == position)
			return SelectableTarget[i];
	}
	return false;
}