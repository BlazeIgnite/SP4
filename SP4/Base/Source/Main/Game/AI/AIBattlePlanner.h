#ifndef AI_BATTLEPLANNER_H
#define AI_BATTLEPLANNER_H

#include <string>

using std::string;

class AIBattlePlanner
{
	string BattlePlan;

public:
	AIBattlePlanner();
	~AIBattlePlanner();

	void SetBattlePlan(string newBattlePlan);
	string GetBattlePlan();
};

#endif