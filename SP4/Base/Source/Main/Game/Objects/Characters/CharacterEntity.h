#ifndef CHARACTER_ENTITY_H
#define CHARACTER_ENTITY_H

#include "../../Base/Source/Main/Engine/Objects/BaseObject.h"
#include <vector>

using std::vector;

class CharacterEntity : public BaseObject
{
protected:
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
	
public:
	CharacterEntity();
	~CharacterEntity();

	//Getters
	int GetLevel() { return Level; }
	float GetHealth() { return Health; }
	float GetMaxHealth(){ return MaxHealth; }
	int GetAbilityPoints(){ return AbilityPoints; }
	int GetMaxAbilityPoints(){ return MaxAbilityPoints; }
	float GetAttack(){ return Attack; }
	float GetDefense(){ return Defense; }
	float GetMagic(){ return Magic; }
	float GetLuck(){ return Luck; }

	//Setters
	void SetLevel(int Level);
	void SetHealth(float Health);
	void SetMaxHealth(float MaxHealth);
	void SetAbilityPoints(int AbilityPoints);
	void SetMaxAbilityPoints(int MaxAbilityPoints);
	void SetAttack(float Attack);
	void SetDefense(float Defense);
	void SetMagic(float Magic);
	void SetLuck(float Luck);

	//Position Stuff
	Position GetPosition(){ return position; }
	void SetPosition(Position position){ this->position = position; }

	void SetDamageMitigation();

	void Init();


private:
	//Character's Base stats
	int	Level;
	float Health;
	float MaxHealth;
	int AbilityPoints;
	int MaxAbilityPoints;
	float Attack;
	float Defense;
	float Magic;
	float Luck;
	Position position;
	//Base Stats End here

	//Final stats
	float DamageMitigation;
	//vector<Skill> Skillset;
};

#endif