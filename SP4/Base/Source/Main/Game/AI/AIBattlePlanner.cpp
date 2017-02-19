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