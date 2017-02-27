#include "AIBattlePlanner.h"


AIBattlePlanner::AIBattlePlanner() : BattlePlan("")
{
}


AIBattlePlanner::~AIBattlePlanner()
{
}

void AIBattlePlanner::SetBattlePlan(string newBattlePlan)
{
	BattlePlan = newBattlePlan;
}

string AIBattlePlanner::GetBattlePlan()
{
	return BattlePlan;
}

bool AIBattlePlanner::GetBattlePlan(string BattlePlan)
{
	if (this->BattlePlan == BattlePlan)
		return true;
	return false;
}

void AIBattlePlanner::UseBattlePlan()
{

}

void AIBattlePlanner::ResetBattlePlan()
{
	BattlePlan = "";
}