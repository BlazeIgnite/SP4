#ifndef ALL_BUFFDEBUFF_H
#define ALL_BUFFDEBUFF_H

#include "../AIBase.h"

class AIBuffDebuff :
	public AIBase
{
public:
	AIBuffDebuff();
	~AIBuffDebuff();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Planning();
	virtual void Execute();
	virtual void Exit();
};

#endif