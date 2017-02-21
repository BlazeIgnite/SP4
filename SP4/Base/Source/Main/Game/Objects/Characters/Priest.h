#ifndef PRIEST_H_
#define PRIEST_H_
#include "Skill.h"
#include "CharacterEntity.h"

class Priest : public CharacterEntity
{
public:
	Priest();
	~Priest();
	virtual void Init(int Level);
	virtual void LevelUp();
	void Update(double dt);
//	OffensiveSkill* skill_1;
};


#endif