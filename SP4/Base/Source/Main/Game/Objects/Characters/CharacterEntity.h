#ifndef CHARACTER_ENTITY_H
#define CHARACTER_ENTITY_H

#include <vector>
#include <string>
#include "../../Base/Source/Main/Engine/Objects/BaseObject.h"
#include "../../Objects/Characters/Skill.h"

using std::string;
using std::vector;

class CharacterEntity : public BaseObject
{
protected:
	//Character's Base stats
	Vector3 Position;
	Vector3 Scale;
	vector<Skill*> SkillList;
	string Name;
	size_t Level;
	size_t Health;
	size_t MaxHealth;
	size_t Attack;
	size_t Defense;
	size_t StatusEffectTimer[4];
	
	//Base Stats End here
	float ExperiencePoints;
	float NormalAttackmultiplier;
	int DamageMitigation;
	bool Defeated;
	bool StatusEffect[4];

public:
	CharacterEntity();
	~CharacterEntity();

	//Getters
	Skill* GetSkillInVector(string SkillName);

	inline Vector3 GetVectorPosition(){ return Position; };
	inline Vector3 GetScale(){ return Scale; };
	inline vector<Skill*>& GetSkillList() { return SkillList; };
	inline string GetName(){ return Name; };
	inline size_t GetLevel() { return Level; };
	inline size_t GetHealth() { return Health; };
	inline size_t GetMaxHealth(){ return MaxHealth; };
	inline size_t GetAttack(){ return Attack; };
	inline size_t GetDefense(){ return Defense; };
	inline size_t GetStunTimer(){ return StatusEffectTimer[0]; };
	inline size_t GetBleedTimer(){ return StatusEffectTimer[1]; };
	inline size_t GetDebuffTimer(){ return StatusEffectTimer[2]; };
	inline size_t GetBuffTimer(){ return StatusEffectTimer[3]; };
	inline bool GetDefeated(){ return Defeated; };
	inline bool GetStunned(){ return StatusEffect[0]; };
	inline bool GetBleeding(){ return StatusEffect[1]; };
	inline bool GetBuffed(){ return StatusEffect[2]; }
	inline bool GetDebuffed(){ return StatusEffect[3]; };

	//Setters
	inline void SetPosition(Vector3 Position){ this->Position = Position; };
	inline void SetScale(Vector3 Scale){ this->Scale = Scale; };
	inline void SetName(string Name){ this->Name = Name; };
	inline void SetLevel(size_t Level){ this->Level = Level; };
	inline void SetHealth(size_t Health){ this->Health = Health; };
	inline void SetMaxHealth(size_t MaxHealth){ this->MaxHealth = MaxHealth; };
	inline void SetAttack(size_t Attack){ this->Attack = Attack; };
	inline void SetDefense(size_t Defense){	this->Defense = Defense; };
	inline void SetStunTimer(size_t StunTimer){ StatusEffectTimer[0] = StunTimer; };
	inline void SetBleedTimer(size_t BleedTimer){ StatusEffectTimer[1] = BleedTimer; };
	inline void SetDebuffTimer(size_t DebuffTimer){ StatusEffectTimer[2] = DebuffTimer; };
	inline void SetBuffTimer(size_t BuffTimer){ StatusEffectTimer[3] = BuffTimer; };
	inline void SetDefeated(bool Defeated){ this->Defeated = Defeated; };
	inline void SetStunned(bool Stunned){ StatusEffect[0] = Stunned; };
	inline void SetBleeding(bool Bleeding){ StatusEffect[1] = Bleeding; };
	inline void SetBuffed(bool Buffed){ StatusEffect[2] = Buffed; };
	inline void SetDebuffed(bool Debuffed){ StatusEffect[3] = Debuffed; };

	virtual void LevelUp() = 0;

	//This sets the Damage Mitigation for every level
	void SetDamageMitigation();
	int GetDamageMitigation(){ return DamageMitigation; }

	virtual void Init(int Level = 1);
	void Update(double dt);
};

#endif