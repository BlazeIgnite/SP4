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

	void SetPlayerName(const std::string&);
	void SetPlayerID(const unsigned int&);
	void SetPlayerGold(const unsigned int&);
	void SetPlayerStageCount(const unsigned int&);
	
	std::string GetPlayerName();
	unsigned int GetPlayerID();
	unsigned int GetPlayerGold();
	unsigned int GetPlayerStageCount();
	std::map<std::string, std::vector<CharacterEntity*>> GetAllUnitList();
	std::vector<CharacterEntity*> GetClassUnitList(std::string&);
	std::map<std::string, unsigned int> GetConsumableList();
	std::map<std::string, unsigned int> GetMaterialList();

	void AddGold(int&);
	void AddCharacter(std::string, CharacterEntity*);
	void AddConsumableItem(std::string, int);
	void AddMaterialItem(std::string, int);

private:
	std::string PlayerName;
	unsigned int PlayerID;
	unsigned int PlayerGold;
	unsigned int FurthestStageCount;

	std::vector<CharacterEntity*> UnitList;
	std::vector<ItemEntity*> ConsumableList;
	std::vector<ItemEntity*> MaterialList;

	std::map<std::string, std::vector<CharacterEntity*>> UnitList;
	std::map<std::string, unsigned int> ConsumableList;
	std::map<std::string, unsigned int> MaterialList;

	ItemEntity* HealthPotion;
	ItemEntity* ManaPotion;
	ItemEntity* Bandage;
	ItemEntity* HolyWater;
	ItemEntity* AtkPotion;
	ItemEntity* DefPotion;
	CharacterEntity* warrior;
	Warrior* warrior_stats;
};

Player::Player()
{
}

Player::~Player()
{
}

void Player::Init(const unsigned int&)
{
	/*warrior = new Warrior();
	AddCharacter(warrior);
	UnitList.push_back(warrior);

	HealthPotion =  new ItemEntity();
	HealthPotion->SetName("HealthPotion");
	HealthPotion->SetAmount(0);
	AddConsumableItem(HealthPotion);

	ManaPotion = new ItemEntity();
	ManaPotion->SetName("ManaPotion");
	ManaPotion->SetAmount(0);
	AddConsumableItem(ManaPotion);

	Bandage = new ItemEntity();
	Bandage->SetName("Bandage");
	Bandage->SetAmount(0);
	AddConsumableItem(Bandage);

	HolyWater = new ItemEntity();
	HolyWater->SetName("HolyWater");
	HolyWater->SetAmount(0);
	AddConsumableItem(HolyWater);

	AtkPotion = new ItemEntity();
	AtkPotion->SetName("AtkPotion");
	AtkPotion->SetAmount(0);
	AddConsumableItem(AtkPotion);

	DefPotion = new ItemEntity();
	DefPotion->SetName("DefPotion");
	DefPotion->SetAmount(0);
	AddConsumableItem(DefPotion);*/
}

void Player::SetPlayerName(const std::string& newName)
{
	this->PlayerName = newName;
}
void Player::SetPlayerID(const unsigned int& newID)
{
	this->PlayerID = newID;
}
void Player::SetPlayerGold(const unsigned int& newGold)
{
	this->PlayerGold = newGold;
}
void Player::SetPlayerStageCount(const unsigned int& newFurthestStageCount)
{
	this->FurthestStageCount = newFurthestStageCount;
}

std::string Player::GetPlayerName()
{
	return this->PlayerName;
}
unsigned int Player::GetPlayerID()
{
	return this->PlayerID;
}
unsigned int Player::GetPlayerGold()
{
	return this->PlayerGold;
}
unsigned int Player::GetPlayerStageCount()
{
	return this->FurthestStageCount;
}

void Player::AddGold(int& AdditionalGold)
{
	this->PlayerGold += AdditionalGold;
}
void Player::AddCharacter(std::string name, CharacterEntity* newCharacter)
{
	//this->UnitList.push_back(newCharacter);
}
void Player::AddConsumableItem(std::string name, int value)
{
	//this->ConsumableList.push_back(*newConsumable);
}
void Player::AddMaterialItem(std::string name, int value)
{
	//this->MaterialList.push_back(*newItem);
}

#endif