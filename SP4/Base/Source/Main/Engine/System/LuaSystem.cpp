#include "LuaSystem.h"
#include "../../Base/Source/Main/Game/Objects/Characters/Player.h"
#include "../../Base/Source/Main/Game/Objects/Characters/Warrior.h"
#include <string>
#include <iostream>

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
	lua_pop(lua, 0);
	return result;
}
float LuaSystem::GetFloatValue(lua_State* lua, const char* varName)
{
	lua_getglobal(lua, varName);
	float result = lua_tointeger(lua, -1);
	lua_pop(lua, 0);
	return result;
}
const char* LuaSystem::GetString(lua_State* lua, const char* varName)
{
	lua_getglobal(lua, varName);
	const char* result = lua_tostring(lua, -1);
	lua_pop(lua, 0);
	return result;
}


void LuaSystem::saveIntValue(const char* varName, const int value, const bool bOverWrite)
{
	lua_State* lua = LuaSystem::Instance().LuaStateList.find("Save Score")->second;
	lua_getglobal(lua, "SaveToLuaFile");
	char outputString[80];
	sprintf(outputString, "%s = %d\n", varName, value);
	lua_pushstring(lua, outputString);
	lua_pushinteger(lua, bOverWrite);
	lua_call(lua, 2, 0);
	std::cout << "........................." << std::endl;;
}
void LuaSystem::saveFloatValue(const char* varName, const float value, const bool bOverWrite)
{
	lua_State* lua = LuaSystem::Instance().LuaStateList.find("Save Score")->second;
	lua_getglobal(lua, "SaveToLuaFile");
	char outputString[80];
	sprintf(outputString, "%s = %6.4f\n", varName, value);
	lua_pushstring(lua, outputString);
	lua_pushinteger(lua, bOverWrite);
	lua_call(lua, 2, 0);
}

lua_State* LuaSystem::GetLuaState(std::string FileName)
{
	lua_State* lua = LuaSystem::Instance().LuaStateList.find(FileName)->second;
	if (lua == nullptr)
	{
		lua = lua_open();
		luaL_openlibs(lua);
		luaL_dofile(lua, FileName.c_str());
		LuaStateList.insert(std::pair<std::string, lua_State*>(FileName, lua));
	}
	return lua;
}

void LuaSystem::GameSave(int SaveFile)
{
	lua_State* lua = LuaSystem::Instance().GetLuaState("Lua//SaveFile.lua");
	lua_getglobal(lua, "SavePlayerFile");
	std::string Input = "";
	Input += "";
	// Player Name
	// Player Tag (1~3)
	// Player Gold
	// Player furthest stage
	// Loop Player crafting item(add item name & count)
	// Loop Player Consumable Item(add item name & count)
	// Loop Player's Unit List - Type, Level
}

void LuaSystem::StageSave()
{
	// Player Name
	// Player Tag (1~3)
	// Collected Gold
	// Collected Material
	// Cleared Percent
	// Units in use - Name, Health, Level, Status Effect, Position
	// Number of Enemy Killed
}

void LuaSystem::LoadGame(int SaveFile)
{
	std::string FilePath = "Lua//PlayerSave" + std::to_string(SaveFile) + ".lua";
	lua_State* lua = LuaSystem::Instance().GetLuaState(FilePath);
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

	unsigned int WarriorCount = GetIntValue(lua, "NumberOfWarrior");
	unsigned int HealerCount = GetIntValue(lua, "NumberOfHealer");
	unsigned int WizardCount = GetIntValue(lua, "NumberOfWizard");

	if (WarriorCount > 0)
	{
		for (int Value = 1; Value <= WarriorCount; ++WarriorCount)
		{
			CharacterEntity* temp = new Warrior();
			std::string VariableName = "Warrior" + std::to_string(Value);
			unsigned int Level = GetIntValue(lua, VariableName.c_str());
			temp->Initvalues(Level);
			Player::Instance().AddCharacter("Warrior", temp);
		}
	}
	if (HealerCount > 0)
	{
		for (int Value = 1; Value <= HealerCount; ++HealerCount)
		{
			CharacterEntity* temp = new Warrior();
			std::string VariableName = "Healer" + std::to_string(Value);
			unsigned int Level = GetIntValue(lua, VariableName.c_str());
			temp->Initvalues(Level);
			Player::Instance().AddCharacter("Healer", temp);
		}
	}
	if (WizardCount > 0)
	{
		for (int Value = 1; Value <= WizardCount; ++WizardCount)
		{
			CharacterEntity* temp = new Warrior();
			std::string VariableName = "Wizard" + std::to_string(Value);
			unsigned int Level = GetIntValue(lua, VariableName.c_str());
			temp->Initvalues(Level);
			Player::Instance().AddCharacter("Wizard", temp);
		}
	}
	// Player Name
	// Player Tag(1~3)
	// Player Gold
	// Player furthest stage
	// Loop Player crafting item(add item name & count)
	// Loop Player Consumable Item(add item name & count)
	// Loop Player's Unit List(add Unit type & level)

}
