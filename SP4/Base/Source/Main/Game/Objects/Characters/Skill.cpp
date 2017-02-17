#include "Skill.h"
//#include "CharacterDatabase.h"

/************************************************/
/*                   Skills                     */
Skill::Skill() : shiftposition(0)
{

}

Skill::~Skill()
{

}

float Skill::SkillBehavior()
{
	return 0;
}

/************************************************/
/*              Offensive skills                */

OffensiveSkill::OffensiveSkill()
{

}

OffensiveSkill::~OffensiveSkill() 
{

}

float OffensiveSkill::SkillBehavior()
{
	if (Character == nullptr || Thetarget == nullptr)
	{
		return 0.f;
	}
	else
	{
		float FinalDamagevalue;
		if (GetScaleFactor() == Scale_Attack)
		{
			FinalDamagevalue = Character->GetAttack();
		}
		else if (GetScaleFactor() == Scale_Magic)
		{
			FinalDamagevalue = Character->GetMagic();
		}

		FinalDamagevalue = FinalDamagevalue * this->GetMultiplier();
		FinalDamagevalue * Thetarget->GetDamageMitigation();
		return FinalDamagevalue;
	}
	return 0.f;
}

void OffensiveSkill::ApplyEffect(STATUSEFFECTS effect, int turns)
{

}

/************************************************/
/*               Revised Skills                 */

Ability::Ability(string name,int id, int abilitycost,int actioncost, float multiplier, STATUSEFFECTS statuseffect, ScaleFactor scalefactor, int timer)
{
	this->name = name;
	this->id = id;
	this->abilitycost = abilitycost;
	this->actioncost = actioncost;
	this->multiplier = multiplier;
	this->statuseffect = statuseffect;
	this->scalefactor = scalefactor;
	this->timer = timer;
}

int Ability::AbilityBehavior()
{
	if (character == nullptr || target == nullptr)
	{
		return 0;
	}
	else if (character->GetAbilityPoints() >= abilitycost)
	{
		float Finaldamage;
		if (scalefactor == Scale_Attack)
		{
			Finaldamage = character->GetAttack();
		}
		else if (scalefactor == Scale_Magic)
		{
			Finaldamage = character->GetMagic();
		}
		Finaldamage *= multiplier;
		Finaldamage *= target->GetDamageMitigation();
		if (statuseffect != No_Effect)
		{
			character->ApplyEffect(statuseffect, timer);
		}
		return Finaldamage;
	}
	return 0;
}