#ifndef MAGE_H_
#define MAGE_H_
#include "CharacterEntity.h"

class Mage : protected CharacterEntity
{
public:
	Mage();
	~Mage();
	virtual void Init(int Level);
	virtual void Levelup();
	void Update(double dt); 
	//OffensiveSkill* skill_1;
};

#endif