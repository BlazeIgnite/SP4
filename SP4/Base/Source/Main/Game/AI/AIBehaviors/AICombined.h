#ifndef AI_COMBINED_H
#define AI_COMBINED_H

#include "../AIBase.h"
class AICombined :
	public AIBase
{
public:
	AICombined();
	~AICombined();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Planning();
	virtual void Execute();
	virtual void Exit();
};

#endif