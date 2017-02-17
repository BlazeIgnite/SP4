#ifndef SKILL_H_
#define SKILL_H_
#include <string>
#include "CharacterEntity.h"
using std::string;


class Skill
{
protected:
	float Multiplier;
	float AbilityPointCost;
	float ActionPointCost;
	int Skill_ID;
	string Skill_name;
	STATUSEFFECTS effect;
public:

	enum ScaleFactor
	{
		Scale_Attack = 1,
		Scale_Magic,

	};

private:

	ScaleFactor scalefactor;
	

public:
	int shiftposition;
	Skill();
	~Skill();
	virtual float SkillBehavior();
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

	void SetScaleFactor(ScaleFactor scalefactor){ this->scalefactor = scalefactor; }
	ScaleFactor GetScaleFactor(){ return scalefactor; }

};


class OffensiveSkill : public Skill
{

private:
	CharacterEntity* Character;
	CharacterEntity* Thetarget;
public:
	OffensiveSkill();
	~OffensiveSkill();
	virtual float SkillBehavior();
	virtual void ApplyEffect(STATUSEFFECTS effect, int turns);
	inline void SetCharacter(CharacterEntity* Character){ this->Character = Character; }
	inline void SetTarget(CharacterEntity* Target){ this->Thetarget = Target; }
};





// Revised skill codes here, will replace the Old Skill with the New Skill
class Ability
{
public:
	enum ScaleFactor
	{
		Scale_Attack = 1,
		Scale_Magic,

	};
	__readonly string name;
	__readonly int id, abilitycost, actioncost , timer;
	__readonly float multiplier;
	__readonly STATUSEFFECTS statuseffect;
	__readonly ScaleFactor scalefactor;
	Ability(string name, int id, int abilitycost, int actioncost, float multiplier, STATUSEFFECTS statuseffect, ScaleFactor scalefactor, int timer);
	~Ability();
	int AbilityBehavior();

	

private:

};
#endif