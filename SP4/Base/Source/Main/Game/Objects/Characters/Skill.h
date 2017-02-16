#ifndef SKILL_H_
#define SKILL_H_
#include <string>
#include "CharacterDatabase.h"
#include "CharacterEntity.h"
using std::string;


class Skill
{
private:
	float Multiplier;
	float AbilityPointCost;
	float ActionPointCost;
	int Skill_ID;
	string Skill_name;
	C_Position RequiredPosition;
	Target RequiredTarget; 
	STATUSEFFECTS effect;
public:

	enum ScaleFactor
	{
		Scale_Attack = 1,
		Scale_Magic,

	};
	

public:
	Skill();
	~Skill();
	virtual void SkillBehavior(ScaleFactor scalefactor);
	//virtual void ApplyEffect(STATUSEFFECTS effect);
	virtual void ApplyEffect(STATUSEFFECTS effect, int turns){};

	//Sets and Gets Skill ID and name if necessary
	void SetSkill_IDs(string Skill_name, int Skill_ID){ this->Skill_name = Skill_name; this->Skill_ID = Skill_ID; }
	string GetSkillname(){ return Skill_name; }
	int GetSkill_ID(){ return Skill_ID; }

	//Sets and Gets AbilityPoint Cost if necessary
	void SetAbilityCost(float AbilityPointCost){ this->AbilityPointCost = AbilityPointCost; }
	float GetAbilityCost(){ return AbilityPointCost; }

	//Sets and gets the Action Points used if necessary
	void SetActionCost(float ActionPointcost){ this->ActionPointCost = ActionPointCost; }
	float GetActionCost(){ return ActionPointCost; }

	//Gets and Sets Multiplier of the Attack necessary
	void SetMultiplier(float Multiplier){ this->Multiplier = Multiplier; }
	float GetMultiplier(){ return Multiplier; }

	void SetSkillPosition(C_Position position){ this->RequiredPosition = position; }
	C_Position GetSkillPosition(){ return RequiredPosition; }

	void SetSkillTarget(Target target){ this->RequiredTarget = target; }
	Target GetSkillTarget(){ return RequiredTarget; }
};


class OffensiveSkill : public Skill
{

private:
	CharacterEntity* Character;
	CharacterEntity* Thetarget;
	ScaleFactor scalefactor;
public:
	OffensiveSkill();
	~OffensiveSkill();
	virtual void SkillBehavior(float Damagemitigation);
	virtual void ApplyEffect(STATUSEFFECTS effect, int turns);
	inline void SetCharacter(CharacterEntity* Character){ this->Character = Character; }
	inline void SetTarget(CharacterEntity* Target){ this->Thetarget = Target; }
	void SetScaleFactor(ScaleFactor scalefactor){ this->scalefactor = scalefactor; }
	void shiftOwnPosition(int shift);
	void shiftEnemyPosition(int shift);
	int shiftposition;
};

class RecoverSkill : public Skill
{
private:
	CharacterEntity* Character;
	CharacterEntity* Thetarget;
	ScaleFactor scalefactor;
public:
	RecoverSkill();
	~RecoverSkill();
	inline void SetCharacter(CharacterEntity* Character){ this->Character = Character; }
	inline void SetTarget(CharacterEntity* Target){ this->Thetarget = Target; }
	virtual void SkillBehavior(float DamageMitigation);
	void SetScaleFactor(ScaleFactor scalefactor){ this->scalefactor = scalefactor; }
};
#endif