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
	AIBase::Init();
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

}

void AIAllAttack::Execute()
{
	
}

void AIAllAttack::Exit()
{
	AIBase::Exit();
}