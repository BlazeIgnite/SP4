#ifndef WARRIOR_H_
#define WARRIOR_H_
#include "CharacterEntity.h"
#include "Skill.h"


class Warrior : public CharacterEntity
{
public:
	OffensiveSkill* skill_1;
public:
	Warrior();
	~Warrior();
	virtual void Initvalues(int Level);
	virtual void Levelup();
	void Update(double dt);
};



#endif