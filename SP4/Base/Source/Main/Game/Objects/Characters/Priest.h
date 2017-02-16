#ifndef PRIEST_H_
#define PRIEST_H_
#include "Skill.h"
#include "CharacterEntity.h"

class Priest : public CharacterEntity, protected OffensiveSkill
{
public:
	Priest();
	~Priest();
	virtual void Initvalues(int Level);
	virtual void Levelup();
	void Update(double dt);
	OffensiveSkill* skill_1;
};


#endif