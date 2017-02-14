#ifndef LUA_SYSTEM_H
#define LUA_SYSTEM_H

#include "../Internal/SingletonTemplate.h"

#include <lua.hpp>
#include <map>

class LuaSystem : public SingletonTemplate<LuaSystem>
{
public:
	LuaSystem();
	~LuaSystem();

	void Init();
	void Exit();

	float GetField(lua_State*, const char*);
	int GetIntValue(lua_State*, const char*);
	float GetFloatValue(lua_State*, const char*);
	const char* GetString(lua_State*, const char*);

	void saveIntValue(const char*, const int, const bool);
	void saveFloatValue(const char*, const float, const bool);

	lua_State* GetLuaState(std::string);

	void GameSave(int);
	void StageSave();
	void LoadGame(int);

	std::map<std::string, lua_State*> LuaStateList;

};

LuaSystem::LuaSystem()
{
}

LuaSystem::~LuaSystem()
{
}










#endif