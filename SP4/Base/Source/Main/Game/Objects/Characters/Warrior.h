#ifndef WARRIOR_H_
#define WARRIOR_H_
#include "CharacterEntity.h"
#include "Skill.h"


class Warrior : protected CharacterEntity
{
public:
	Warrior();
	~Warrior();
	virtual void Init(int Level);
	void Update(double dt);
	virtual void LevelUp();
};

#endif