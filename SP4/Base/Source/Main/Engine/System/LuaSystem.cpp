#include "LuaSystem.h"
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
	// Player Name
	// Player Tag(1~3)
	// Player Gold
	// Player furthest stage
	// Loop Player crafting item(add item name & count)
	// Loop Player Consumable Item(add item name & count)
	// Loop Player's Unit List(add Unit type & level)

}
