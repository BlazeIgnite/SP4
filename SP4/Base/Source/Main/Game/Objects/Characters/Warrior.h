#ifndef WARRIOR_H_
#define WARRIOR_H_
#include "CharacterEntity.h"
#include "Skill.h"


class Warrior : public CharacterEntity
{
private:
	OffensiveSkill* skill_1;
public:
	Warrior();
	~Warrior();
	virtual void Init(int Level);
	virtual void Levelup();
};



#endif