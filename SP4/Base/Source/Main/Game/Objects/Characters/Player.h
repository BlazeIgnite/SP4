#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

#include "CharacterEntity.h"

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

private:
	std::string PlayerName;
	unsigned int PlayerID;
	unsigned int PlayerGold;
	unsigned int FurthestStageCount;
	std::vector<CharacterEntity> UnitList;
	//std::vector<ItemEntity> ConsumableList;
	//std::vector<ItemEntity> MaterialList;



};

Player::Player()
{
}

Player::~Player()
{
}





#endif