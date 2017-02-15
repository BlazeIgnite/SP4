#ifndef AI_BASE_H
#define AI_BASE_H

#include <vector>

#include "AIStateManager.h"

using std::vector;

class AIBase
{
protected:
	// The troops that the AI will have 
	//vector<CharacterEntity> TroopList;
	AIStateManager* stateHolder;
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