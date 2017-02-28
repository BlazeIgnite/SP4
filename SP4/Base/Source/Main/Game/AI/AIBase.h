#ifndef AI_BASE_H
#define AI_BASE_H

#include <vector>
#include "AIStateManager.h"
#include "AIBattlePlanner.h"
#include "../Objects/Characters/CharacterEntity.h"

using std::vector;

class AIBase
{
protected:
	// The troops that the AI will have 
	vector<AIBattlePlanner*> BattlePlanHolder;
	AIStateManager* stateHolder;

	size_t m_AITurnCostHolder;

	bool Calculate(Skill*);
	bool CalculateCheck(Skill*);
public:
	AIBase();
	~AIBase();

	virtual void Init();
	virtual void Update(double dt) = 0;
	virtual void Planning() = 0;
	virtual void Execute() = 0;
	virtual void Exit();
};

#endif