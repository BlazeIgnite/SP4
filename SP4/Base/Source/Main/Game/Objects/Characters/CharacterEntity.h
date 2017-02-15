#ifndef CHARACTER_ENTITY_H
#define CHARACTER_ENTITY_H

#include "../../Base/Source/Main/Engine/Objects/BaseObject.h"
#include <vector>
#include "CharacterDatabase.h"

using std::vector;

class CharacterEntity : public BaseObject 
{
protected:
	
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

	virtual void Levelup(){};

	//Position Stuff
	C_Position GetPosition(){ return position; }
	void SetPosition(C_Position position){ this->position = position; }

	void SetDamageMitigation();

	virtual void Init(int Level);


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
	C_Position position;
	//Base Stats End here

	//Final stats
	float DamageMitigation;
	
	//vector<Skill> Skillset;
};

#endif