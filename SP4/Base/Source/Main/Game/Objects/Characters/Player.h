#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <map>

#include "../../Base/Source/Main/Engine/Internal/SingletonTemplate.h"
#include "CharacterEntity.h"
#include "../Items/ItemEntity.h"
#include "Warrior.h"

class Player : public SingletonTemplate<Player>
{
public:
	Player();
	~Player();

	void Init(const unsigned int&);
	void Update(double dt);
	void SetPlayerName(const std::string&);
	void SetPlayerID(const unsigned int&);
	void SetPlayerGold(const unsigned int&);
	void SetPlayerStageCount(const unsigned int&);
	
	std::string GetPlayerName();
	unsigned int GetPlayerID();
	unsigned int GetPlayerGold();
	unsigned int GetPlayerStageCount();

	std::map<std::string, std::vector<CharacterEntity*>>& GetAllUnitList();
	std::vector<CharacterEntity*>& GetClassUnitList(std::string);
	std::map<std::string, unsigned int>& GetConsumableList();
	std::map<std::string, unsigned int>& GetMaterialList();

	//std::vector<CharacterEntity*> GetClassUnitList(std::string);


	void AddGold(int&);
	void AddCharacter(std::string, CharacterEntity*);
	void AddConsumableItem(std::string, int);
	void AddMaterialItem(std::string, int);

private:
	std::string PlayerName;
	unsigned int PlayerID;
	unsigned int PlayerGold;
	unsigned int FurthestStageCount;

	std::map<std::string, std::vector<CharacterEntity*>> UnitList;
	std::map<std::string, unsigned int> ConsumableList;
	std::map<std::string, unsigned int> MaterialList;

	ItemEntity* HealthPotion;
	ItemEntity* ManaPotion;
	ItemEntity* Bandage;
	ItemEntity* AtkPotion;
	ItemEntity* DefPotion;

	ItemEntity* RedHerb;
	ItemEntity* BlueHerb;
	ItemEntity* WhiteHerb;

	bool Pressed = false;

	CharacterEntity* warrior;
};
#endif