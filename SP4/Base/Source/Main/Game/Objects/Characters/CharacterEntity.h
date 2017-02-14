#ifndef CHARACTER_ENTITY_H
#define CHARACTER_ENTITY_H

#include "../../Base/Source/Main/Engine/Objects/BaseObject.h"
#include <vector>
using std::vector;

class CharacterEntity : public BaseObject
{
	enum Position
	{
		Position_Front = 1,
		Position_Middle,
		Position_Back,
	};
	enum Target
	{
		Target_Front = 1,
		Target_Middle,
		Target_Back,
	};
	class Skill
	{
	public:
		Skill();
		~Skill();
		void SkillBehavior();
	};
	
public:
	CharacterEntity();
	~CharacterEntity();

	//Getters
	int GetLevel();
	float GetHealth(); 
	float GetMaxHealth();
	float GetAbilityPoints();
	float GetMaxAbilityPoints();
	float GetAttack();
	float GetDefense();
	float GetMagic();
	float GetLuck();

	//Setters
	void SetLevel(int Level);
	void SetHealth(float Health);
	void SetMaxHealth(float MaxHealth);
	void SetAbilityPoints(float AbilityPoints);
	void SetMaxAbilityPoints(float MaxAbilityPoints);
	void SetAttack(float Attack);
	void SetDefense(float Defense);
	void SetMagic(float Magic);
	void SetLuck(float Luck);

	void SetDamageMitigation();

	void Init();

private:
	//Character's Base stats
	int	Level;
	float Health;
	float MaxHealth;
	float AbilityPoints;
	float MaxAbilityPoints;
	float Attack;
	float Defense;
	float Magic;
	float Luck;
	//Base Stats End here

	//Final stats
	float Damagemitigation;
	vector<Skill> Skillset;

	
};

CharacterEntity::CharacterEntity()
{
}

CharacterEntity::~CharacterEntity()
{
}








#endif