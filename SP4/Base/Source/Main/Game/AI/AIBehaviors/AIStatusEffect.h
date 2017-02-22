#ifndef AI_STATUS_EFFECT_H
#define AI_STATUS_EFFECT_H

#include "../AIBase.h"
#include <map>

using std::map;

class AIStatusEffect :
	public AIBase
{
	map<size_t, map<size_t, bool>> m_PlayerTroopStatusE;

public:
	AIStatusEffect();
	~AIStatusEffect();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Planning();
	virtual void Execute();
	virtual void Exit();

	void SetPlayerTroopStatusE(size_t troopPosition, size_t statusID, bool newStatusE);
	bool GetPlayerTroopStatusE(size_t troopPosition, size_t statusID);

};

#endif