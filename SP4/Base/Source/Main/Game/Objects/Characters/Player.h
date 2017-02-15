#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

#include "CharacterEntity.h"
#include "../Items/ItemEntity.h"

class Player
{
public:
	Player();
	~Player();

	void SetPlayerName(const std::string&);
	void SetPlayerID(const unsigned int&);
	void SetPlayerGold(const unsigned int&);
	void SetPlayerStageCount(const unsigned int&);
	
	std::string GetPlayerName();
	unsigned int GetPlayerID();
	unsigned int GetPlayerGold();
	unsigned int GetPlayerStageCount();
	std::vector<CharacterEntity*> GetUnitList();

	void AddGold(int&);
	void AddCharacter(CharacterEntity*);
	void AddConsumableItem(ItemEntity*);
	void AddMaterialItem(ItemEntity*);

private:
	std::string PlayerName;
	unsigned int PlayerID;
	unsigned int PlayerGold;
	unsigned int FurthestStageCount;
	std::vector<CharacterEntity> UnitList;
	std::vector<ItemEntity> ConsumableList;
	std::vector<ItemEntity> MaterialList;
};

Player::Player()
{
}

Player::~Player()
{
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
	return this->GetPlayerGold;
}
unsigned int Player::GetPlayerStageCount()
{
	return this->FurthestStageCount;
}

void Player::AddGold(int& AdditionalGold)
{
	this->PlayerGold += AdditionalGold;
}
void Player::AddCharacter(CharacterEntity* newCharacter)
{
	this->UnitList.push_back(*newCharacter);
}
void Player::AddConsumableItem(ItemEntity* newConsumable)
{
	this->ConsumableList.push_back(*newConsumable);
}
void Player::AddMaterialItem(ItemEntity* newItem)
{
	this->MaterialList.push_back(*newItem);
}


#endif