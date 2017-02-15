#include "Skill.h"

/************************************************/
/*                   Skills                     */
Skill::Skill()
{

}

Skill::~Skill()
{

}

void Skill::SkillBehavior(ScaleFactor scalefactor)
{

}

/************************************************/
/*              Offensive skills                */

OffensiveSkill::OffensiveSkill()
{

}

OffensiveSkill::~OffensiveSkill() 
{

}

void OffensiveSkill::SkillBehavior(float Damagemitigation)
{
	if (Character == nullptr || Thetarget == nullptr)
	{
		return;
	}
	else
	{
		float FinalDamagevalue;
		if (scalefactor == Scale_Attack)
		{
			FinalDamagevalue = Character->GetAttack();
		}
		else if (scalefactor == Scale_Magic)
		{
			FinalDamagevalue = Character->GetMagic();
		}
		if (Character->GetPosition() == GetSkillPosition())
		{
			if (Thetarget->GetPosition() == GetSkillTarget())
			{
				FinalDamagevalue = FinalDamagevalue * this->GetMultiplier();
				FinalDamagevalue = FinalDamagevalue * (1.f - Damagemitigation);
				float Targetfinalhealth = Thetarget->GetHealth();
				Targetfinalhealth -= FinalDamagevalue;
				Thetarget->SetHealth(Targetfinalhealth);

			}
		}
	}

}

/************************************************/
/*            Status Effect skills              */

StatusEffectSkill::StatusEffectSkill()
{

}

StatusEffectSkill::~StatusEffectSkill()
{

}

void StatusEffectSkill::SkillBehavior(float Damagemitigation)
{
	if (Character == nullptr || Thetarget == nullptr)
	{
		return;
	}
	else
	{
		float FinalDamagevalue;
		if (scalefactor == Scale_Attack)
		{
			FinalDamagevalue = Character->GetAttack();
		}
		else if (scalefactor == Scale_Magic)
		{
			FinalDamagevalue = Character->GetMagic();
		}
		if (Character->GetPosition() == GetSkillPosition())
		{
			if (Thetarget->GetPosition() == GetSkillTarget())
			{
				FinalDamagevalue = FinalDamagevalue * this->GetMultiplier();
				FinalDamagevalue = FinalDamagevalue * (1.f - Damagemitigation);
				float Targetfinalhealth = Thetarget->GetHealth();
				Targetfinalhealth -= FinalDamagevalue;
				Thetarget->SetHealth(Targetfinalhealth);

			}
		}
	}

}