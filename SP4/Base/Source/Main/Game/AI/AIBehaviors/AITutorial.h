#pragma once

#include "../AIBase.h"

class AITutorial :
	public AIBase
{
private:
	size_t m_Turn;

public:
	AITutorial();
	~AITutorial();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Planning();
	virtual void Execute();
	virtual void Exit();

};

