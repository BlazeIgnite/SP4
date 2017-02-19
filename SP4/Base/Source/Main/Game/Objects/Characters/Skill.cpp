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

Ability::Ability()
{
	
}

void Ability::ApplyAbility(CharacterEntity* Character, CharacterEntity* target)
{
	
}


Bash::Bash() : 
name("Bash")
, id(0001)
, abilitycost(5)
, actioncost(20)
, statuseffect(Stun)
, timer(3)
, multiplier(0.65f)
, shiftposition(0)
{

}