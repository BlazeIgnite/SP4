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
	BattlePlanHolder = new AIBattlePlanner();
}

void AIBase::Exit()
{
	if (stateHolder != nullptr)
	{
		delete stateHolder;
		stateHolder = nullptr;
	}
	if (BattlePlanHolder != nullptr)
	{
		delete BattlePlanHolder;
		BattlePlanHolder = nullptr;
	}
}