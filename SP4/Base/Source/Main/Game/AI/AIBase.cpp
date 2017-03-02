#include "AIBase.h"


AIBase::AIBase()
{
	Init();
}


AIBase::~AIBase()
{
	Exit();
}

void AIBase::Init()
{
	stateHolder = new AIStateManager();
	m_AITurnCostHolder = 0;
	m_target = 0;
	m_Attacker = 0;
	m_DamageCaused = 0;

	m_Attacking = false;
}

bool AIBase::Calculate(Skill* skillUsed)
{
	int turncost;
	turncost = m_AITurnCostHolder - skillUsed->GetActionCost();
	if (turncost < 0)
		return false;
	else
	{
		m_AITurnCostHolder = turncost;
		return true;
	}
}

bool AIBase::CalculateCheck(Skill* skillUsed)
{
	int turncost;
	turncost = m_AITurnCostHolder - skillUsed->GetActionCost();
	if (turncost < 0)
		return false;
	else
		return true;
}

void AIBase::SetAttacking(bool attacking)
{
	m_Attacking = attacking;
}

bool AIBase::GetAttacking()
{
	return m_Attacking;

}

void AIBase::SetDamageCaused(size_t dmg)
{
	m_DamageCaused = dmg;
}

size_t AIBase::GetDamageCaused()
{
	return m_DamageCaused;
}

size_t AIBase::GetTarget()
{
	return m_target;
}

size_t AIBase::GetAttacker()
{
	return m_Attacker;
}

void AIBase::Exit()
{
	if (stateHolder != nullptr)
	{
		delete stateHolder;
		stateHolder = nullptr;
	}
	/*for (vector<AIBattlePlanner*>::iterator it = BattlePlanHolder.end(); it != BattlePlanHolder.begin();  it--)
	{
		if ((*it) != nullptr)
			delete *it;
		BattlePlanHolder.pop_back();
	}*/
}