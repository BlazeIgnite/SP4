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
		{
			Skill* temp = BattleSystem::Instance().GetAITroops().at(0)->GetSkillInVector("Basic Attack");
			AIBattlePlanner* TurnOne = new AIBattlePlanner(temp, 0, 0);
			BattlePlanHolder.push_back(TurnOne);
			break; 
		}
		case 3:
		{
			Skill* temp = BattleSystem::Instance().GetAITroops().at(0)->GetSkillInVector("Basic Attack");
			AIBattlePlanner* TurnThree = new AIBattlePlanner(temp, 0, 0);
			BattlePlanHolder.push_back(TurnThree);
			//BattlePlanHolder->SetBattlePlan("Turn 3");
			break;
		}
		default:
			break;
		}
	}
	else
	{
		for (size_t j = 0; j < 2; j++)
		{
			AIBattlePlanner* AttackPhase = new AIBattlePlanner(BattleSystem::Instance().GetAITroops().at(0)->GetSkillInVector("Basic Attack"), 0, Math::RandIntMinMax(0, 1));
			BattlePlanHolder.push_back(AttackPhase);
		}
		//BattlePlanHolder->SetBattlePlan("Normal Attack");
	}
	stateHolder->SetState("Execute");
}

void AITutorial::Execute()
{
	if (BattlePlanHolder.size() > 0)
	{
		AIBattlePlanner* ABP = BattlePlanHolder.back();
		m_target = ABP->GetTarget();
		if (BattleSystem::Instance().GetPlayerTroops().at(m_target)->GetDefeated())
		{
			delete ABP;
			BattlePlanHolder.pop_back();
			return;
		}
		m_Attacking = true;
		m_DamageCaused = BattleSystem::Instance().DamageCalculation(ABP->GetTarget(), ABP->GetSkill());
		delete ABP;
		BattlePlanHolder.pop_back();
	}

	if (BattlePlanHolder.size() == 0 && !m_Attacking)
	{
		m_AITurnCostHolder = 100;
		m_Turn++;
		stateHolder->ResetState();
		BattleSystem::Instance().SetPlayerTurn(true);
	}

}

void AITutorial::Exit()
{
}