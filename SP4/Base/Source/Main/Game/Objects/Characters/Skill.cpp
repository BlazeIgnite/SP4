#include "Skill.h"
//#include "CharacterDatabase.h"

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

OffensiveSkill::OffensiveSkill() : shiftposition(0)
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
				FinalDamagevalue = FinalDamagevalue * (Damagemitigation);
				float Targetfinalhealth = Thetarget->GetHealth();
				Targetfinalhealth -= FinalDamagevalue;
				Thetarget->SetHealth(Targetfinalhealth);
				shiftOwnPosition(shiftposition);
			}
		}
	}

}

void OffensiveSkill::shiftOwnPosition(int shift)
{
	if (shift > 0 && Character->GetPosition() != Position_Back)
	{
		Character->SetPosition(static_cast<C_Position>(Character->GetPosition() + shift));
		if (Character->GetPosition() > Position_Back)
		{
			Character->SetPosition(Position_Back);
		}
	}
	else if (shift < 0 && Character->GetPosition() != Position_Front)
	{
		Character->SetPosition(static_cast<C_Position>(Character->GetPosition() + shift));
		if (Character->GetPosition() < Position_Front)
		{
			Character->SetPosition(Position_Front);
		}
	}
}
void OffensiveSkill::shiftEnemyPosition(int shift)
{

}

void OffensiveSkill::ApplyEffect(STATUSEFFECTS effect, int turns)
{

}

/************************************************/
/*            Status Effect skills              */

RecoverSkill::RecoverSkill()
{

}

RecoverSkill::~RecoverSkill()
{

}

void RecoverSkill::SkillBehavior()
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
				float Targetfinalhealth = Thetarget->GetHealth();
				Targetfinalhealth -= FinalDamagevalue;
				Thetarget->SetHealth(Targetfinalhealth);

			}
		}
	}

}