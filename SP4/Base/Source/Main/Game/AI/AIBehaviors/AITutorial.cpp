#include "AITutorial.h"
#include "../../Systems/BattleSystem.h"

AITutorial::AITutorial()
{
	Init();
}


AITutorial::~AITutorial()
{
}

void AITutorial::Init()
{
	m_Turn = 1;
}

void AITutorial::Update(double dt)
{
	if (!BattleSystem::Instance().GetPlayerTurn())
	{
		if (stateHolder->GetState(""))
			stateHolder->SetState("Planning");
		else if (stateHolder->GetState("Planning"))
			Planning();
		else if (stateHolder->GetState("Execute"))
			Execute();
	}
}

void AITutorial::Planning()
{
	if (m_Turn < 4)
	{
		switch (m_Turn)
		{
		case 1:
			BattlePlanHolder->SetBattlePlan("Turn 1");
			break;
		case 2:
			BattlePlanHolder->SetBattlePlan("Turn 2");
			break;
		case 3:
			BattlePlanHolder->SetBattlePlan("Turn 3");
			break;
		}
	}
	else
	{
		BattlePlanHolder->SetBattlePlan("Normal Attack");
	}
	stateHolder->SetState("Execute");
}

void AITutorial::Execute()
{
	if (m_Turn < 4)
	{
		if (BattlePlanHolder->GetBattlePlan("Turn 1"))
		{
			BattleSystem::Instance().DamageCalculation(0, BattleSystem::Instance().GetAITroopAttacking(0)->GetSkillInVector("Basic Attack"));
		}
		else if (BattlePlanHolder->GetBattlePlan("Turn 2"))
		{
		}
		else if (BattlePlanHolder->GetBattlePlan("Turn 3"))
		{
		}
	}

	BattlePlanHolder->ResetBattlePlan();
	stateHolder->ResetState();
}

void AITutorial::Exit()
{
}