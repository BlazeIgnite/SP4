#include "AIBattlePlanner.h"


AIBattlePlanner::AIBattlePlanner()
{
}

AIBattlePlanner::AIBattlePlanner(Skill* SkillUsed, size_t Attacker, size_t Target)
: m_SkillUsed(SkillUsed)
, m_Attacker(Attacker)
, m_Target(Target)
{
}

AIBattlePlanner::~AIBattlePlanner()
{
}

void AIBattlePlanner::SetSkill(Skill* skill)
{
	m_SkillUsed = skill;
}
void AIBattlePlanner::SetAttacker(size_t attacker)
{
	m_Attacker = attacker;
}
void AIBattlePlanner::SetTarget(size_t target)
{
	m_Target = target;
}

Skill* AIBattlePlanner::GetSkill()
{
	return m_SkillUsed;
}
size_t AIBattlePlanner::GetAttacker()
{
	return m_Attacker;
}
size_t AIBattlePlanner::GetTarget()
{
	return m_Target;
}