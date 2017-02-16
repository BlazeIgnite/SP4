#ifndef AI_STATE_MANAGER_H
#define AI_STATE_MANAGER_H

#include <string>

using std::string;

class AIStateManager
{
	string state;
public:
	AIStateManager();
	~AIStateManager();

	void SetState(string newString);
	string GetState(); 
	bool GetState(string State);
};

#endif