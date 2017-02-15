#ifndef BATTLE_SYSTEM_H
#define BATTLE_SYSTEM_H

#include "../Internal/SingletonTemplate.h"
#include "../AI/AIBase.h"
#include "../Objects/Characters/CharacterEntity.h"
#include "../Objects/Characters/Player.h"

class BattleSystem : public SingletonTemplate<BattleSystem>
{
public:
	BattleSystem();
	~BattleSystem();

	AIBase* AI;
	Player* player;

	void Attack();

	bool PlayerTurn;
};

#endif