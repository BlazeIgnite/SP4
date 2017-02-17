#include "Player.h"
//#include "../../Base/Source/Main/Engine/System/LuaSystem.h"
#include "../../Game/Mains/Application.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Init(const unsigned int& PlayerTag)
{
	UnitList = std::map<std::string, std::vector<CharacterEntity*>>();
	UnitList.insert(std::pair<std::string, std::vector<CharacterEntity*>>("Warrior", std::vector<CharacterEntity*>()));
	UnitList.insert(std::pair<std::string, std::vector<CharacterEntity*>>("Healer", std::vector<CharacterEntity*>()));
	UnitList.insert(std::pair<std::string, std::vector<CharacterEntity*>>("Wizard", std::vector<CharacterEntity*>()));
	//LuaSystem::Instance().LoadGame(PlayerTag);
	ConsumableList.insert(std::pair < std::string, unsigned int>("Red Potion", 0));
	ConsumableList.insert(std::pair < std::string, unsigned int>("Blue Potion", 0));
	ConsumableList.insert(std::pair < std::string, unsigned int>("HealthPotion", 0));
	ConsumableList.insert(std::pair < std::string, unsigned int>("HealthPotion", 0));
	ConsumableList.insert(std::pair < std::string, unsigned int>("HealthPotion", 0));

	MaterialList.insert(std::pair < std::string, unsigned int>("Red Herb", 0));
	MaterialList.insert(std::pair < std::string, unsigned int>("Blue Herb", 0));
	MaterialList.insert(std::pair < std::string, unsigned int>("White Herb", 0));
	MaterialList.insert(std::pair < std::string, unsigned int>("Empty Bottle", 0));
	MaterialList.insert(std::pair < std::string, unsigned int>("Cloth", 0));

	item = new ItemEntity();
	AddConsumableItem("Red Potion", 4);

	AddMaterialItem("Red Herb", 5);
	AddMaterialItem("Blue Herb", 5);
	AddMaterialItem("White Herb", 3);
	AddMaterialItem("Empty Bottle", 3);
	AddMaterialItem("Cloth", 5);
}

void Player::Update(double dt)
{
	

}

//Player Setter
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

//Player Getter
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

//List Getter
std::map<std::string, std::vector<CharacterEntity*>>& Player::GetAllUnitList()
{
	return this->UnitList;
}
std::vector<CharacterEntity*>& Player::GetClassUnitList(std::string Name)
{
	return this->UnitList.find(Name)->second;
}
//std::vector<CharacterEntity*> Player::GetClassUnitList(std::string Name)
//{
//	return this->UnitList.find(Name)->second;
//}
std::map<std::string, unsigned int>& Player::GetConsumableList()
{
	return this->ConsumableList;
}
std::map<std::string, unsigned int>& Player::GetMaterialList()
{
	return this->MaterialList;
}

//Add
void Player::AddGold(int& AdditionalGold)
{
	this->PlayerGold += AdditionalGold;
}
void Player::AddCharacter(std::string Name, CharacterEntity* newCharacter)
{

	std::map<string, std::vector<CharacterEntity*>>::iterator itr = UnitList.find(Name);
	if (itr == UnitList.end())
	{
		std::vector < CharacterEntity* > emptyCharacterEntity;
		emptyCharacterEntity.push_back(newCharacter);
		UnitList[Name] = emptyCharacterEntity;
		//UnitList[Name].push_back(newCharacter);
		//UnitList.insert(std::pair <string, std::vector<CharacterEntity*>>(Name, newCharacter));
	}
	else
		this->UnitList.find(Name)->second.push_back(newCharacter);
}
void Player::AddConsumableItem(std::string Name, int Amount)
{
	std::map<string, unsigned int>::iterator itr = ConsumableList.find(Name);
	if (itr == ConsumableList.end())
	{
		ConsumableList[Name] = Amount;
	}
	this->ConsumableList.find(Name)->second += Amount;
}
void Player::AddMaterialItem(std::string Name, int Amount)
{
	std::map<string, unsigned int>::iterator itr = MaterialList.find(Name);
	if (itr == MaterialList.end())
	{
		MaterialList[Name] = Amount;
	}
	this->MaterialList.find(Name)->second += Amount;
}