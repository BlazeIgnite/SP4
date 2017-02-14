#include "AIBase.h"


AIBase::AIBase()
{
}


AIBase::~AIBase()
{
}

void AIBase::Init()
{
	stateHolder = new AIStateManager();
}

void AIBase::Exit()
{
	if (stateHolder)
	{
		delete stateHolder;
		stateHolder = NULL;
	}
}