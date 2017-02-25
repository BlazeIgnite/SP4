#include "LuaSystem.h"
#include "../../Base/Source/Main/Game/Objects/Characters/Player.h"
#include "../../Base/Source/Main/Game/Objects/Characters/Warrior.h"
#include <string>
#include <iostream>


LuaSystem::LuaSystem()
{
}

LuaSystem::~LuaSystem()
{
	Exit();
}

void LuaSystem::Init()
{
	LuaStateList = std::map<std::string, lua_State*>();
}

void LuaSystem::Exit()
{
	std::map<std::string, lua_State*>::iterator it = LuaStateList.begin();
	while (it != LuaStateList.end())
	{
		//lua_close(it->second);
		it->second = nullptr;
		it = LuaStateList.erase(it);
	}
}

float LuaSystem::GetField(lua_State* lua, const char* key)
{
	int result;
	lua_pushstring(lua, key);
	lua_gettable(lua, -2);
	result = lua_tonumber(lua, -1);
	lua_pop(lua, 1);
	return result;
}
int LuaSystem::GetIntValue(lua_State* lua, const char* varName)
{
	lua_getglobal(lua, varName);
	int result = lua_tointeger(lua, -1);
	return result;
}
float LuaSystem::GetFloatValue(lua_State* lua, const char* varName)
{
	lua_getglobal(lua, varName);
	float result = lua_tointeger(lua, -1);
	return result;
}
const char* LuaSystem::GetString(lua_State* lua, const char* varName)
{
	lua_getglobal(lua, varName);
	const char* result = lua_tostring(lua, -1);
	return result;
}


void LuaSystem::saveIntValue(const char* varName, const int value, const bool bOverWrite)
{
	lua_State* lua = LuaStateList.find("Save Score")->second;
	lua_getglobal(lua, "SaveToLuaFile");
	char outputString[80];
	sprintf(outputString, "%s = %d\n", varName, value);
	lua_pushstring(lua, outputString);
	lua_pushinteger(lua, bOverWrite);
	lua_call(lua, 2, 0);
	lua = nullptr;
}
void LuaSystem::saveFloatValue(const char* varName, const float value, const bool bOverWrite)
{
	lua_State* lua = LuaStateList.find("Save Score")->second;
	lua_getglobal(lua, "SaveToLuaFile");
	char outputString[80];
	sprintf(outputString, "%s = %6.4f\n", varName, value);
	lua_pushstring(lua, outputString);
	lua_pushinteger(lua, bOverWrite);
	lua_call(lua, 2, 0);
	lua = nullptr;
}

lua_State* LuaSystem::GetLuaState(std::string FileName)
{
	std::map<std::string, lua_State*>::iterator lua = LuaStateList.find(FileName);
	if (lua == LuaStateList.end())
	{
		lua_State* temp;
		temp = lua_open();
		luaL_openlibs(temp);
		luaL_dofile(temp, FileName.c_str());
		LuaStateList.insert(std::pair<std::string, lua_State*>(FileName, temp));
		return temp;
	}
	return lua->second;
}

void LuaSystem::ReloadLuaState(std::string FileName)
{
	lua_close(GetLuaState(FileName));
	LuaStateList.erase(FileName);
	lua_State* temp = lua_open();
	luaL_openlibs(temp);
	luaL_dofile(temp, FileName.c_str());
	LuaStateList.insert(std::pair<std::string, lua_State*>(FileName, temp));
}

void LuaSystem::GameSave()
{
	ReloadLuaState("Lua\\SaveFile.lua");
	lua_State* lua = GetLuaState("Lua\\SaveFile.lua");
	lua_getglobal(lua, "SavePlayerFile");
	std::string Input = "";
	int WarriorSize, MageSize, PriestSize;
	Input += ("PlayerName = \"" + Player::Instance().GetPlayerName() + "\"");
	Input += ("\nPlayerTag = " + std::to_string(Player::Instance().GetPlayerID()));
	Input += ("\nPlayerGold = " + std::to_string(Player::Instance().GetPlayerGold()));
	Input += ("\nPlayerFurthestStage = " + std::to_string(Player::Instance().GetPlayerStageCount()));
			 
	Input += ("\nRedHerbCount = " + std::to_string(Player::Instance().GetMaterialList().find("Red Herb")->second));
	Input += ("\nWhiteHerbCount = " + std::to_string(Player::Instance().GetMaterialList().find("White Herb")->second));
	Input += ("\nEmptyBottleCount = " + std::to_string(Player::Instance().GetMaterialList().find("Empty Bottle")->second));
	Input += ("\nClothCount = " + std::to_string(Player::Instance().GetMaterialList().find("Cloth")->second));
			 
	Input += ("\nRedPotionCount = " + std::to_string(Player::Instance().GetConsumableList().find("Red Potion")->second));
	Input += ("\nAttackPotionCount = " + std::to_string(Player::Instance().GetConsumableList().find("Attack Potion")->second));
	Input += ("\nDefencePotionCount = " + std::to_string(Player::Instance().GetConsumableList().find("Defence Potion")->second));
	Input += ("\nAttackPotionCount = " + std::to_string(Player::Instance().GetConsumableList().find("Bandage")->second));
			 
	Input += ("\nWarriorCount = " + std::to_string(Player::Instance().GetClassUnitList("Warrior").size()));
	Input += ("\nMageCount = " + std::to_string(Player::Instance().GetClassUnitList("Mage").size()));
	Input += ("\nPriestCount = " + std::to_string(Player::Instance().GetClassUnitList("Priest").size()));

	if (Player::Instance().GetClassUnitList("Warrior").size() > 0)
	{
		for (std::map<int, CharacterEntity*>::iterator it = Player::Instance().GetClassUnitList("Warrior").begin(); it != Player::Instance().GetClassUnitList("Warrior").end(); ++it)
		{
			Input += "\nWarrior" + std::to_string(it->first + 1) + " = " + std::to_string(it->second->GetLevel());
		}
	}
	if (Player::Instance().GetClassUnitList("Mage").size() > 0)
	{
		for (std::map<int, CharacterEntity*>::iterator it = Player::Instance().GetClassUnitList("Mage").begin(); it != Player::Instance().GetClassUnitList("Mage").end(); ++it)
		{
			Input += "\nMage" + std::to_string(it->first + 1) + " = " + std::to_string(it->second->GetLevel());
		}
	}
	if (Player::Instance().GetClassUnitList("Priest").size() > 0)
	{
		for (std::map<int, CharacterEntity*>::iterator it = Player::Instance().GetClassUnitList("Priest").begin(); it != Player::Instance().GetClassUnitList("Priest").end(); ++it)
		{
			Input += "\nPriest" + std::to_string(it->first + 1) + " = " + std::to_string(it->second->GetLevel());
		}
	}
	lua_pushinteger(lua, Player::Instance().GetPlayerID());
	lua_pushstring(lua, Input.c_str());
	lua_call(lua, 2, 0);
	lua = nullptr;
}

void LuaSystem::LoadGame(int SaveFile)
{
	std::string FilePath = "Lua//PlayerSave" + std::to_string(SaveFile) + ".lua";
	ReloadLuaState(FilePath);
	lua_State* lua = GetLuaState(FilePath);
	Player::Instance().SetPlayerName(GetString(lua, "PlayerName"));
	Player::Instance().SetPlayerID(GetIntValue(lua, "PlayerTag"));
	Player::Instance().SetPlayerGold(GetIntValue(lua, "PlayerGold"));
	Player::Instance().SetPlayerStageCount(GetIntValue(lua, "PlayerFurthestStage"));

	Player::Instance().AddMaterialItem("Red Herb", GetIntValue(lua, "RedHerbCount"));
	Player::Instance().AddMaterialItem("Blue Herb", GetIntValue(lua, "BlueHerbCount"));
	Player::Instance().AddMaterialItem("Empty Bottle", GetIntValue(lua, "EmptyBottleCount"));
	Player::Instance().AddMaterialItem("Cloth", GetIntValue(lua, "ClothCount"));
	Player::Instance().AddMaterialItem("White Herb", GetIntValue(lua, "WhiteHerbCount"));

	Player::Instance().AddConsumableItem("Red Potion", GetIntValue(lua, "RedPotionCount"));
	Player::Instance().AddConsumableItem("Blue Potion", GetIntValue(lua, "BluePotionCount"));
	Player::Instance().AddConsumableItem("Attack Potion", GetIntValue(lua, "AttackPotionCount"));
	Player::Instance().AddConsumableItem("Defence Potion", GetIntValue(lua, "DefencePotionCount"));
	Player::Instance().AddConsumableItem("Bandage", GetIntValue(lua, "BandageCount"));

	unsigned int WarriorCount = GetIntValue(lua, "WarriorCount");
	unsigned int PriestCount = GetIntValue(lua, "PriestCount");
	unsigned int WizardCount = GetIntValue(lua, "MageCount");

	if (WarriorCount > 0)
	{
		for (int Value = 1; Value <= WarriorCount; ++Value)
		{
			CharacterEntity* temp = new Warrior();
			std::string VariableName = "Warrior" + std::to_string(Value);
			unsigned int Level = GetIntValue(lua, VariableName.c_str());
			temp->Init(Level);
			Player::Instance().AddCharacter("Warrior", temp);
		}
	}
	if (PriestCount > 0)
	{
		for (int Value = 1; Value <= PriestCount; ++Value)
		{
			CharacterEntity* temp = new Priest();
			std::string VariableName = "Priest" + std::to_string(Value);
			unsigned int Level = GetIntValue(lua, VariableName.c_str());
			temp->Init(Level);
			Player::Instance().AddCharacter("Priest", temp);
		}
	}
	if (WizardCount > 0)
	{
		for (int Value = 1; Value <= WizardCount; ++Value)
		{
			CharacterEntity* temp = new Mage();
			std::string VariableName = "Mage" + std::to_string(Value);
			unsigned int Level = GetIntValue(lua, VariableName.c_str());
			temp->Init(Level);
			Player::Instance().AddCharacter("Mage", temp);
		}
	}
	// Player Name
	// Player Tag(1~3)
	// Player Gold
	// Player furthest stage
	// Loop Player crafting item(add item name & count)
	// Loop Player Consumable Item(add item name & count)
	// Loop Player's Unit List(add Unit type & level)
	lua = nullptr;
}