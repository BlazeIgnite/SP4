#pragma once

#include "../AIBase.h"

class AITutorial :
	public AIBase
{
private:
	size_t m_Turn;

	size_t m_BattleNumber;

public:
	AITutorial();
	~AITutorial();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Planning();
	virtual void Execute();
	virtual void Exit();

	void SetBattleNumber(size_t BattleNumber) { m_BattleNumber = BattleNumber; };
};

