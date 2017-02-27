#ifndef PRIEST_H_
#define PRIEST_H_
#include "Skill.h"
#include "CharacterEntity.h"

class Synergist : public CharacterEntity
{
public:
	Synergist();
	~Synergist();
	virtual void Init(int Level);
	virtual void LevelUp();
	void Update(double dt);
//	OffensiveSkill* skill_1;
};


#endif