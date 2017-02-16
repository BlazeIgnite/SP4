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

	for (int i = 0; i < 50; i++)
	{
		warrior = new Warrior();
		warrior->Init(1);
		AddCharacter("Warrior", warrior);
	}
	
	HealthPotion = new ItemEntity();
	AddConsumableItem("Red Potion", 4);

	//ManaPotion = new ItemEntity();
	//ManaPotion->SetName("ManaPotion");
	//ManaPotion->SetAmount(0);
	//AddConsumableItem("ManaPotion", 1);

	//Bandage = new ItemEntity();
	//Bandage->SetName("Bandage");
	//Bandage->SetAmount(0);
	//AddConsumableItem("Bandage", 1);

	//AtkPotion = new ItemEntity();
	//AtkPotion->SetName("AtkPotion");
	//AtkPotion->SetAmount(0);
	//AddConsumableItem("AtkPotion", 1);.

	//DefPotion = new ItemEntity();
	//DefPotion->SetName("DefPotion");
	//DefPotion->SetAmount(0);
	//AddConsumableItem("DefPotion", 1);


	            
}

void Player::Update(double dt)
{
	std::string temp = "Warrior";

	std::cout << warrior->GetHealth() << std::endl;

	if (Application::IsKeyPressed('Y'))
	{
		//GetConsumableList().find("Red Potion")->second;
		if (!Pressed && GetConsumableList().find("Red Potion")->second > 0)
		{
			AddConsumableItem("Red Potion", -1);
			HealthPotion->Use("Red Potion", warrior);
			Pressed = true;
		}
	}
	else
	{
		if (Pressed)
			Pressed = false;
	}
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
std::vector<CharacterEntity*>& Player::GetClassUnitList(std::string& Name)
{
	return this->UnitList.find(Name)->second;
}
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
	this->UnitList.find(Name)->second.push_back(newCharacter);

	//UnitList.insert(std::pair<std::string, CharacterEntity* >(Name, newCharacter));
}
void Player::AddConsumableItem(std::string Name, int Amount)
{
	this->ConsumableList.find(Name)->second += Amount;
}
void Player::AddMaterialItem(std::string Name, int Amount)
{
	this->MaterialList.find(Name)->second += Amount;
}