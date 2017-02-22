#include "AIAllAttack.h"
#include "../../Systems/BattleSystem.h"

AIAllAttack::AIAllAttack()
{
}

AIAllAttack::~AIAllAttack()
{
}

void AIAllAttack::Init()
{
}

void AIAllAttack::Update(double dt)
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

void AIAllAttack::Planning()
{
	BattlePlanHolder->SetBattlePlan("Normal Attack");
	stateHolder->SetState("Execute");
}

void AIAllAttack::Execute()
{
	if (BattlePlanHolder->GetBattlePlan("Normal Attack"))
	{
		for (size_t i = 0; i < BattleSystem::Instance().GetNumberOfAITroopAlive(); i++)
		{
			if (BattleSystem::Instance().CanActivateSkill(BattleSystem::Instance().GetAITroopAttacking(i), 0, BattleSystem::Instance().GetAITroopAttacking(i)->GetSkillInVector("Basic Attack")));
			BattleSystem::Instance().DamageCalculation(0, BattleSystem::Instance().GetAITroopAttacking(i)->GetSkillInVector("Basic Attack"));
		}
	}
	BattlePlanHolder->SetBattlePlan("");
	stateHolder->SetState("");
	BattleSystem::Instance().SetPlayerTurn(true);
}

void AIAllAttack::Exit()
{
}