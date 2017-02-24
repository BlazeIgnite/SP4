#ifndef AI_STATUS_EFFECT_H
#define AI_STATUS_EFFECT_H

#include "../AIBase.h"
#include <map>

using std::map;

class AIStatusEffect :
	public AIBase
{
	map<CharacterEntity*, vector<Skill*>> m_SkillAvailable;

	// Iterators
	map<CharacterEntity*, vector<Skill*>>::iterator m_SkillAvailableIterator;
	vector<Skill*>::iterator m_SkillIterator;


	size_t m_target;
	size_t m_Turns;
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