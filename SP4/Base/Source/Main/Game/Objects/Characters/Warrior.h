#ifndef WARRIOR_H_
#define WARRIOR_H_
#include "CharacterEntity.h"
#include "Skill.h"


class Warrior : public CharacterEntity , protected OffensiveSkill
{
private:
	OffensiveSkill *skill_1;
public:
	Warrior();
	~Warrior();
	virtual void Init();
};



#endif