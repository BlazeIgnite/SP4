#ifndef AI_STATUS_EFFECT_H
#define AI_STATUS_EFFECT_H

#include "../AIBase.h"

class AIStatusEffect :
	public AIBase
{
public:
	AIStatusEffect();
	~AIStatusEffect();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Planning();
	virtual void Execute();
	virtual void Exit();
};

#endif