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

	lua_State* GetLuaState(std::string);
	void ReloadLuaState(std::string);

	void GameSave();
	void LoadGame(int);

	std::map<std::string, lua_State*> LuaStateList;

};










#endif