#ifndef AI_BASE_H
#define AI_BASE_H

#include <map>
#include <vector>
#include "AIStateManager.h"
#include "../Objects/Characters/CharacterEntity.h"

using std::map;
using std::vector;
class AIBase
{
protected:
	// The troops that the AI will have 
	map<string, vector<CharacterEntity*>> TroopList;
	AIStateManager* stateHolder;
public:
	AIBase();
	~AIBase();

	virtual void Init();
	virtual void Update(double dt) = 0;
	virtual void Planning() = 0;
	virtual void Execute() = 0;
	virtual void Exit();

	virtual	void AddTroop(string Name, CharacterEntity* Troop);
	virtual map<string, vector<CharacterEntity*>> GetAllAIList();
	virtual vector<CharacterEntity*> GetClassAIList(string& Name);
	virtual vector<CharacterEntity*> GetClassAIList(string Name);
};

#endif