#ifndef MAGE_H_
#define MAGE_H_
#include "Skill.h"
#include "CharacterEntity.h"

class Mage : public CharacterEntity, protected OffensiveSkill
{
public:
	Mage();
	~Mage();
	virtual void Init(int Level);
	virtual void Levelup();
	void Update(double dt); 
	OffensiveSkill* skill_1;
};

#endif