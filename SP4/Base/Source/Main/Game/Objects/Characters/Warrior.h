#ifndef WARRIOR_H_
#define WARRIOR_H_
#include "CharacterEntity.h"
#include "Skill.h"


class Warrior : public CharacterEntity
{
public:
	OffensiveSkill* skill_1;
private:
public:
	Warrior();
	~Warrior();
	void Init(const Vector3 Position, Vector3 Scale);
	virtual void Init(int Level);
	void Update(double dt);
	virtual void Levelup();
	Vector3 Position;
	Vector3 Scale;
};



#endif