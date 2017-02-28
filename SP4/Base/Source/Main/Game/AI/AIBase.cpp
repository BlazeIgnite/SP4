#include "AIBase.h"


AIBase::AIBase()
{
	Init();
}


AIBase::~AIBase()
{
	//Exit();
}

void AIBase::Init()
{
	stateHolder = new AIStateManager();
	m_AITurnCostHolder = 0;
}

bool AIBase::Calculate(Skill* skillUsed)
{
	int turncost;
	turncost = m_AITurnCostHolder - skillUsed->GetActionCost();
	if (turncost < 0)
		return false;
	else
		return true;
}

void AIBase::Exit()
{
	if (stateHolder != nullptr)
	{
		delete stateHolder;
		stateHolder = nullptr;
	}
	for (vector<AIBattlePlanner*>::iterator it = BattlePlanHolder.end(); it != BattlePlanHolder.begin();  it--)
	{
		if ((*it) != nullptr)
			delete *it;
		BattlePlanHolder.pop_back();
	}
}