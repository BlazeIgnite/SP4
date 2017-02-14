#ifndef SKILL_H_
#define SKILL_H_
#include <string>
#include "StatusEffects.h"
#include "CharacterEntity.h"
using std::string;


class Skill : protected CharacterEntity
{
	CharacterEntity* TheCharacter;
	CharacterEntity* theTarget;
public:
	Skill();
	~Skill();
	void SkillBehavior(Position position,Target target);
private:
	int Skill_ID;
	string Skill_name;

};

#endif