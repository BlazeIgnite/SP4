#include "AIStateManager.h"


AIStateManager::AIStateManager() : state("")
{
}

AIStateManager::~AIStateManager()
{
}

void AIStateManager::SetState(string newState)
{
	state = newState;
}

string AIStateManager::GetState()
{
	return state;
}