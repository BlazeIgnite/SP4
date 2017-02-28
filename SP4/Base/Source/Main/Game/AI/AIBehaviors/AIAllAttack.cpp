#include "AIAllAttack.h"
#include "../../Systems/BattleSystem.h"

AIAllAttack::AIAllAttack()
{
	Init();
}

AIAllAttack::~AIAllAttack()
{
}

void AIAllAttack::Init()
{
	m_AITurnCostHolder = BattleSystem::Instance().GetTurnCost();
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
	bool planningDone = false;
	CharacterEntity* tempCE = BattleSystem::Instance().GetAITroops().at(BattleSystem::Instance().GetNumberOfAITroopAlive() - 1);
	for (auto it : BattleSystem::Instance().GetAITroops())
	{
		if (!it.second->GetDefeated())
		{
			size_t tempTarget = (size_t)Math::RandIntMinMax(0, 1);
			if (BattleSystem::Instance().GetPlayerTroopAttacking(tempTarget) != nullptr)
			{
				if (BattleSystem::Instance().CanActivateSkill(it.second, tempTarget, it.second->GetSkillInVector("Basic Attack")))
				{
					AIBattlePlanner* temp = new AIBattlePlanner();
					temp->SetSkill(it.second->GetSkillInVector("Basic Attack"));
					temp->SetAttacker(it.first);
					temp->SetTarget(tempTarget);
					BattlePlanHolder.push_back(temp);
				}
				if (!BattleSystem::Instance().CanActivateSkill(tempCE, tempTarget, tempCE->GetSkillInVector("Basic Attack")))
					planningDone = true;
			}
		}
	}
	if (planningDone)
		stateHolder->SetState("Execute");
}

void AIAllAttack::Execute()
{
	//if (BattlePlanHolder->GetBattlePlan("Normal Attack"))
	//{
	//	for (size_t i = 0; i < BattleSystem::Instance().GetNumberOfAITroopAlive(); i++)
	//	{
	//		size_t target;
	//		while (true)
	//		{
	//			target = (size_t)Math::RandIntMinMax(0, 1);
	//			if (BattleSystem::Instance().GetPlayerTroopAttacking(i) != nullptr || !BattleSystem::Instance().GetPlayerTroopAttacking(i)->GetDefeated())
	//			break;
	//		}
	//		if (BattleSystem::Instance().CanActivateSkill(BattleSystem::Instance().GetAITroopAttacking(i), target,  BattleSystem::Instance().GetAITroopAttacking(i)->GetSkillInVector("Basic Attack")))
	//			BattleSystem::Instance().DamageCalculation(target, BattleSystem::Instance().GetAITroopAttacking(i)->GetSkillInVector("Basic Attack"));
	//	}
	//}
	//BattlePlanHolder->SetBattlePlan("");
	//stateHolder->SetState("");



	BattleSystem::Instance().SetPlayerTurn(true);
}

void AIAllAttack::Exit()
{
}