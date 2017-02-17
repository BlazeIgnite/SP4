#include "AIDefault.h"
#include "../../Systems/BattleSystem.h"
#include <iostream>

using std::cout;
using std::endl;

AIDefault::AIDefault()
{
}


AIDefault::~AIDefault()
{
}

void AIDefault::Init()
{
	AIBase::Init();
}

void AIDefault::Update(double dt)
{
	if (!BattleSystem::Instance().GetPlayerTurn())
	{
		if (stateHolder->GetState(""))
		stateHolder->SetState("Thinking");
		if (stateHolder->GetState("Thinking"))
			Planning();
		else if (stateHolder->GetState("Execute"))
			Execute();
	}
}

void AIDefault::Planning()
{
	stateHolder->SetState("Execute");
}

void AIDefault::Execute()
{
	//cout << "I end my turn" << endl;
	//BattleSystem::Instance().SetPlayerTurn(true);
	stateHolder->SetState("");
}

void AIDefault::Exit()
{
	AIBase::Exit();
}