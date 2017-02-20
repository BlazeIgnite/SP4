#include "Skill.h"
//#include "CharacterDatabase.h"




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


Bash::Bash()
{
	name = "Bash";
	id = 0001;
	actioncost = 30;
	statuseffect = Stun;
	timer = 3;
	multiplier = 0.30f;
	shiftposition = 0;
}

Rush::Rush()
{
	name = "Rush";
	id = 0002;
	actioncost = 25;
	statuseffect = No_Effect;
	timer = 3;
	multiplier = 0.30f;
	shiftposition = 1;
}

Taunt::Taunt()
{
	name = "Taunt";
	id = 0003;
	actioncost = 35;
	statuseffect = Buff;
	timer = 1;
}

Stab::Stab()
{
	name = "Stab";
	id = 0004;
	actioncost = 25;
	statuseffect = Bleed;
	timer = 3;
}

DivineE::DivineE()
{
	name = "Divine Execution";
	id = 0005;
	actioncost = 75;
	multiplier = 1.50f;
}

MagicB::MagicB()
{
	name = "Magic Bolt";
	id = 0006;
	actioncost = 30;
	multiplier = 0.75f;
}

BFlash::BFlash()
{
	name = "Blinding Flash";
	id = 0007;
	actioncost = 30;
	multiplier = 0.15f;
	statuseffect = Stun;
	timer = 1;
}

UnholyI::UnholyI()
{
	name = "Unholy Incantation";
	id = 0010;
	actioncost = 40;
	multiplier = 0.20f;
	shiftposition = 2;

}

MiasmicC::MiasmicC()
{
	name = "Miasmic Cloud";
	id = 0011;
	actioncost = 40;
	statuseffect = Debuff;
	timer = 3;
}

Ars::Ars()
{
	name = "Ars Arcanum";
	id = 0012;
	actioncost = 100;
	multiplier - 0.90f;
	statuseffect = Bleed;
	statuseffect2 = Debuff;
	timer = 2;
}

Heal::Heal()
{
	name = "Heal";
	id = 0013;
	actioncost = 25;
	multiplier = 0.45f;
}

Esuna::Esuna()
{
	name = "Esuna";
	id = 0014;
	actioncost = 40;
}

UnholyG::UnholyG()
{
	name = "Unholy Gift";
	id = 0015;
	actioncost = 35;
	multiplier = 0.50f;
}

DivineG::DivineG()
{
	name = "Divine Guidance";
	id = 0016;
	actioncost = 30;
	statuseffect = Buff;
	timer = 3;
}

GuardianA::GuardianA()
{
	name = "Guardian Angel";
	id = 0017;
	actioncost = 80;
	statuseffect = Buff;
	timer = 3;
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