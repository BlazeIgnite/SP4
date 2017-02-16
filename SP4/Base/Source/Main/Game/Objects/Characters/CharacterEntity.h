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
	bool GetDefeated() { return Defeated; }

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
	void SetDefeated(bool Defeated);

	virtual void Levelup(){};

	//Position Stuff
	C_Position GetPosition(){ return position; }
	void SetPosition(C_Position position){ this->position = position; }
	//This sets the Damage Mitigation for every level
	void SetDamageMitigation();
	float GetDamageMitigation(){ return DamageMitigation; }

	virtual void Init(int Level);
	virtual void Update(double dt);
	//virtual void Init(int Level);


private:
	//Character's Base stats
	C_Position position;
	int	Level;
	int AbilityPoints;
	int MaxAbilityPoints;
	float Health;
	float MaxHealth;
	float Attack;
	float Defense;
	float Magic;
	float Luck;
	//Base Stats End here

	int ID;

	//Final stats
	float DamageMitigation;
	
	bool Defeated;
	
	//vector<Skill> Skillset;
};

#endif