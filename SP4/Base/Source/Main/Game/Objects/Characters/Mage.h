#ifndef MAGE_H_
#define MAGE_H_
#include "CharacterEntity.h"

class Mage : public CharacterEntity
{
public:
	Mage();
	~Mage();
	virtual void Init(int Level);
	virtual void LevelUp(bool init);
	void Update(double dt); 
	//OffensiveSkill* skill_1;
};

#endif