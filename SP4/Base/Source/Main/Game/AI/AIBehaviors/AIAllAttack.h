#ifndef AI_ALL_ATTACK_H
#define AI_ALL_ATTACK_H

#include "../AIBase.h"

class AIAllAttack : public AIBase
{
public:
	AIAllAttack();
	~AIAllAttack();
	
	virtual void Init();
	virtual void Update(double dt);
	virtual void Planning();
	virtual void Execute();
	virtual void Exit();
};

#endif