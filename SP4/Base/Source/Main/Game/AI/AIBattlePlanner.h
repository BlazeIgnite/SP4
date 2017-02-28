#ifndef AI_BATTLEPLANNER_H
#define AI_BATTLEPLANNER_H

#include <string>
#include "../Objects/Characters/Skill.h"

using std::string;

class AIBattlePlanner
{
	Skill* m_SkillUsed;
	size_t m_Attacker;
	size_t m_Target;

public:
	AIBattlePlanner();
	~AIBattlePlanner();

	void SetSkill(Skill* skill);
	void SetAttacker(size_t attacker);
	void SetTarget(size_t target);

	Skill* GetSkill();
	size_t GetAttacker();
	size_t GetTarget();
};

#endif