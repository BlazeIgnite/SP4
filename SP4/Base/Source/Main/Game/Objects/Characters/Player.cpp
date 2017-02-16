#include "Player.h"
//#include "../../Base/Source/Main/Engine/System/LuaSystem.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Init(const unsigned int& PlayerTag)
{
	//LuaSystem::Instance().LoadGame(PlayerTag);

	HealthPotion = new ItemEntity();
	HealthPotion->SetName("HealthPotion");
	HealthPotion->SetAmount(0);

	ManaPotion = new ItemEntity();
	ManaPotion->SetName("ManaPotion");
	ManaPotion->SetAmount(0);

	Bandage = new ItemEntity();
	Bandage->SetName("Bandage");
	Bandage->SetAmount(0);

	HolyWater = new ItemEntity();
	HolyWater->SetName("HolyWater");
	HolyWater->SetAmount(0);

	AtkPotion = new ItemEntity();
	AtkPotion->SetName("AtkPotion");
	AtkPotion->SetAmount(0);

	DefPotion = new ItemEntity();
	DefPotion->SetName("DefPotion");
	DefPotion->SetAmount(0);

	warrior = new Warrior();
	warrior->Init(1);
	AddCharacter("ChiBai", warrior);

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
std::map<std::string, std::vector<CharacterEntity*>> Player::GetAllUnitList()
{
	return this->UnitList;
}
std::vector<CharacterEntity*> Player::GetClassUnitList(std::string& Name)
{
	return this->UnitList.find(Name)->second;
}
std::vector<CharacterEntity*> Player::GetClassUnitList(std::string Name)
{
	return this->UnitList.find(Name)->second;
}
std::map<std::string, unsigned int> Player::GetConsumableList()
{
	return this->ConsumableList;
}
std::map<std::string, unsigned int> Player::GetMaterialList()
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
	if (itr == ConsumableList.end())
	{
		MaterialList[Name] = Amount;
	}
	this->MaterialList.find(Name)->second += Amount;
}