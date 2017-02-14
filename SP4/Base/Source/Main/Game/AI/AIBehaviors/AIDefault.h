#ifndef AI_DEFAULT_H
#define AI_DEFAULT_H

#include "../AIBase.h"
class AIDefault :
	public AIBase
{
public:
	AIDefault();
	~AIDefault();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Planning();
	virtual void Execute();
	virtual void Exit();

};

#endif